#pragma once

#include "JuceHeader.h"
#include "Transport.h"
#include "NoteHarmony.h"

class DelayVoice
{

    public :
    
    DelayVoice() {}
    
    void prepare(double sampleRate, int blockSize)
    {
        transport.prepare(sampleRate, blockSize);
        std::fill(notesOn, notesOn + 127, 0);
        std::fill(noteID, noteID + 127, 0);
        notes.clear();
     //   notes.reserve(128);
    }
    
    void process(juce::AudioBuffer<float>& buffer,juce::MidiBuffer& midiMessages, juce::AudioPlayHead* playhead, float mult, int intervalAdd, bool clear, bool swap, juce::MidiBuffer& midiBuffer, bool isHarmony, int offsetNote, bool mode, int oct, int transpose)
    {
        if (clear)
        {
            midiBuffer.clear();
        }
        auto numSamples = buffer.getNumSamples();
        transport.process(playhead, numSamples);
        if (playhead != nullptr)
        {
            playhead->getCurrentPosition(info);
        }
        
        if (info.isPlaying)
        {
            for (auto message: midiMessages)
            {
                int octScale = (oct * 12);
                auto currentMessage = message.getMessage();
                auto noteNum = currentMessage.getNoteNumber() + transpose + octScale;
                auto position = message.samplePosition;
                auto velocity = currentMessage.getVelocity();
                int interNote = (noteNum-transpose) % 12;

                if (isHarmony)
                {
                    if (mode)
                    {
                        intervalAddition = returnHarmonyAddition(interNote, true, intervalAdd);
                    } else
                    {
                        intervalAddition = returnVoiceAddition(interNote, true, intervalAdd);
                    }
                } else
                {
                    intervalAddition = offsetNote;
                }
                
                if (currentMessage.isNoteOn())
                {
                    //notes.push_back(NoteInfo());
                    setTimeData(noteNum+intervalAddition,velocity,idCounter,position,mult,false);
                    noteID[noteNum] = idCounter; // Store Id Counter
                    idCounter++;
                    idCounter = idCounter % 100; // this is a bit dumb and hacky
                }
                
                if (currentMessage.isNoteOff())
                {
                    auto idValue = noteID[noteNum];
                    removeTimeData(noteNum+intervalAddition, idValue, position);
                }
            }
        }

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            double ppqVal = transport.ppqPositions[sample]; // Gonna have to ditch this way of using timiing information from the Host, as looping is causing issues. (Planning for events in the future, that may not happen as the loop restarts, and results in a time in the past in transports PPQ)
            
            for (int i = 0; i < 100; i++) // this is a bad way of doing thigns as well. Could be a dynamic array, and just use for auto note in notes instead
            {
                if (noteInfo[i].shouldPlayNote)
                {
                    noteInfo[i].delayOnTime = transport.ppqPositions[noteInfo[i].startSample] + mult;
                    noteInfo[i].shouldPlayNote = false;
                }
                
                if (ppqVal >= noteInfo[i].delayOnTime && noteInfo[i].toggleOn)
                {
                    if (noteInfo[i].noteNumber < 127 && noteInfo[i].noteNumber > 0)
                    {
                        auto message = juce::MidiMessage::noteOn(1, noteInfo[i].noteNumber, (juce::uint8)noteInfo[i].velocity);
                        processNote(message,sample,midiBuffer);
                    } else
                    {
                        noteInfo[i].repeat = false;
                    }
                    
                    noteInfo[i].toggleOn = false;
                    if (noteInfo[i].repeat)
                    {
                        auto idValue = noteID[noteInfo[i].noteNumber];
                        removeTimeData(noteInfo[i].noteNumber, idValue, sample);
                    }
                }
                
                if(noteInfo[i].shouldEndNote)
                {
                    if(!noteInfo[i].repeat)
                    {
                       noteInfo[i].delayOffTime = transport.ppqPositions[noteInfo[i].endSample] + mult;
                    }
                    
                    if(noteInfo[i].repeat)
                    {
                        noteInfo[i].delayOffTime = transport.ppqPositions[noteInfo[i].endSample];
                    }
                    
                    noteInfo[i].shouldEndNote = false;
                }
                
                if (ppqVal >= noteInfo[i].delayOffTime && noteInfo[i].toggleOff)
                {
                    if (noteInfo[i].noteNumber < 127 && noteInfo[i].noteNumber > 0)
                    {
                        midiBuffer.addEvent(juce::MidiMessage::noteOff(1, noteInfo[i].noteNumber), sample);
                        
                        if (noteInfo[i].repeat)
                        {
                            int interadd = 0;
                            int interNote = (noteInfo[i].noteNumber-transpose) % 12;
                           interadd = returnHarmonyAddition(interNote, true, intervalAdd);
                           setTimeData(noteInfo[i].noteNumber+interadd, (juce::uint8)noteInfo[i].velocity, noteID[idCounter], sample, mult, true);
                            idCounter++;
                            idCounter = idCounter % 100;
                            noteID[noteInfo[i].noteNumber+interadd] = idCounter;
                        }
                    } else {
                        noteInfo[i].noteNumber = 0;
                        noteInfo[i].endSample = 0;
                        noteInfo[i].repeat = false;
                    }
                    noteInfo[i].toggleOff = false;
                }
                if (!info.isPlaying && noteInfo[i].etoggleOff)
                {
                    if (noteInfo[i].noteNumber < 127 && noteInfo[i].noteNumber > 0)
                    {
                        midiBuffer.addEvent(juce::MidiMessage::noteOff(1, noteInfo[i].noteNumber), sample);
                    }
                    noteInfo[i].noteNumber = 0;
                    noteInfo[i].endSample = 0;
                    noteInfo[i].etoggleOff = false;
                }
            }
        }
        if (swap)
        {
            midiMessages.swapWith(midiBuffer);
        } 
    }
    
private:
    int intervalAddition = 0;
    void processNote(juce::MidiMessage message, int samplePos,juce::MidiBuffer& midiBuffer) {
        midiBuffer.addEvent(message, samplePos);
        return;
    }
      
    void removeTimeData(int noteNum, int idValue, int samplePosition)
    {
        noteInfo[idValue].endSample = samplePosition;
        noteInfo[idValue].shouldPlayNote = false;
        noteInfo[idValue].shouldEndNote = true;
        noteInfo[idValue].toggleOff  = true;
    }
    
    void setTimeData(int noteNum, int velocity, int idValue, int position, float timemult, bool repeat)
    {
        noteInfo[idValue].startSample = position;
        noteInfo[idValue].noteNumber = noteNum;
        noteInfo[idValue].shouldPlayNote = true;
        noteInfo[idValue].toggleOn  = true;
        noteInfo[idValue].velocity = velocity;
        noteInfo[idValue].timemult = timemult;
        noteInfo[idValue].etoggleOff = true;
        noteInfo[idValue].repeat = repeat;
    }
    
    Transport transport;
    int idCounter = 0;
    int notesOn[127];
    int noteID[127];
    
    juce::AudioPlayHead::CurrentPositionInfo info;
    
    struct NoteInfo
    {
        int startSample = 0;
        int endSample = 0;
        int noteNumber = 0;
        int velocity = 0;
        bool shouldPlayNote = false;
        bool shouldEndNote = false;
        double delayOnTime = 0;
        double delayOffTime = 0;
        bool toggleOn =false;
        bool toggleOff =false;
        float timemult = 0.0f;
        bool etoggleOff =false;
        bool repeat = false;
    };
    struct NoteInfo noteInfo[127];
    
    //std::vector<NoteInfo> notes; // not used, but could be better alternative
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayVoice)
};

