/*
  ==============================================================================

    AmountOfNotes.h
    Created: 7 Nov 2022 9:06:39pm
    Author:  Mouldy Soul

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Transport.h"

class AmountOfNotes
{
    public :
    
    void prepare()
    {
        heldNotes.clear();
        notesToPlay.clear();
    }
    
    void process(juce::MidiBuffer& midiMessages, int transposeAmount)
    {
        midiBuffer.clear();
        for (auto message : midiMessages)
        {
            auto currentMessage = message.getMessage();
            auto noteNum = currentMessage.getNoteNumber();
            int velocity = currentMessage.getVelocity();
            int position = message.samplePosition;
            
                if (currentMessage.isNoteOnOrOff())
                {
                    setVoices(noteNum, transposeAmount, false);
                    
                    if (currentMessage.isNoteOn())
                    {
                        addNoteOns(noteNum);
                       
                    }
                    for (auto note : notesToPlay)
                    {
                        currentMessage.setNoteNumber(note);
                        midiBuffer.addEvent(currentMessage,position);
                    }
                    
                    if (currentMessage.isNoteOff())
                    {
                        heldNotes.removeValue(noteNum);
                        
                        if (heldNotes.size() == 0)
                        {
                            notesToPlay.removeValue(noteNum);
                            
                            for (auto note : notesToPlay)
                            {
                                currentMessage.setNoteNumber(note);
                                midiBuffer.addEvent(currentMessage,position);
                            }
                            removeHarmonyNotes(noteNum);
                        }
                    }
                }
        }

        midiMessages.swapWith(midiBuffer);
    }
    
    void setVoices(int note, int transpose, bool mode)
    {
        interNote = (note-transpose) % 12;
        intervalAdd1 = returnVoiceAddition(interNote, mode, 3) + note + transpose;
        intervalAdd2 = returnVoiceAddition(interNote, mode, 2) + note + transpose;
        intervalAdd3 = returnVoiceAddition(interNote, mode, 3) + note + transpose;
        intervalAdd4 = returnVoiceAddition(interNote, mode, 4) + note + transpose;
    }
    
    
    void addNoteOns (int note)
    {
        heldNotes.add(note);
        notesToPlay.add(note);
        notesToPlay.add(intervalAdd1);
        notePairs[note].intervalAdd1 = intervalAdd1;
        notesToPlay.add(intervalAdd2);
        notePairs[note].intervalAdd2 = intervalAdd2;
        notesToPlay.add(intervalAdd3);
        notePairs[note].intervalAdd3 = intervalAdd3;
        notesToPlay.add(intervalAdd4);
        notePairs[note].intervalAdd4 = intervalAdd4;
    }
    
    void removeHarmonyNotes(int note)
    {
        notesToPlay.removeValue(notePairs[note].intervalAdd1);
        notesToPlay.removeValue(notePairs[note].intervalAdd2);
        notesToPlay.removeValue(notePairs[note].intervalAdd3);
        notesToPlay.removeValue(notePairs[note].intervalAdd4);
        notesToPlay.clear();
    }
    
                                          
    private:
    juce::MidiBuffer midiBuffer;
    int intervalAdd1 = 0;
    int intervalAdd2 = 0;
    int intervalAdd3 = 0;
    int intervalAdd4 = 0;
    int interNote = 0;
    juce::SortedSet<int> heldNotes;
    juce::SortedSet<int> notesToPlay;
    
    struct noteHarmony
    {
        int intervalAdd1 = 0;
        int intervalAdd2 = 0;
        int intervalAdd3 = 0;
        int intervalAdd4 = 0;
    };
    
    struct noteHarmony notePairs[127];
    
    int returnVoiceAddition(int interNote, bool majorOn, int intervalSpacing)
    {
        int intervalAddition;
        
        switch(intervalSpacing)
        {
            case 3:
                if (majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = 4;
                            break;
                        case 1:
                            intervalAddition = 3;
                            break;
                        case 2:
                            intervalAddition = 2;
                            break;
                        case 3:
                            intervalAddition = 2;
                            break;
                        case 4:
                            intervalAddition = 3;
                            break;
                        case 5:
                            intervalAddition = 2;
                        case 6:
                            intervalAddition = 4;
                            break;
                        case 7:
                            intervalAddition = 5; // or 2?
                            break;
                        case 8:
                            intervalAddition = 4; // or 2?
                            break;
                        case 9:
                            intervalAddition = 3;
                            break;
                        case 10:
                            intervalAddition = 2;
                            break;
                        case 11:
                            intervalAddition = 1;
                            break;
                    }
                }
                
                if (!majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = 4;
                            break;
                        case 1:
                            intervalAddition = 3;
                            break;
                        case 2:
                            intervalAddition = 2;
                            break;
                        case 3:
                            intervalAddition = 1;
                            break;
                        case 4:
                            intervalAddition = 5;
                            break;
                        case 5:
                            intervalAddition = 4;
                            break;
                        case 6:
                            intervalAddition = 3;
                            break;
                        case 7:
                            intervalAddition = 2; // or 2?
                            break;
                        case 8:
                            intervalAddition = 1; // or 2?
                            break;
                        case 9:
                            intervalAddition = 3;
                            break;
                        case 10:
                            intervalAddition = 2;
                            break;
                        case 11:
                            intervalAddition = 1;
                            break;
                    }
                }
                break;
            case 4:
                if (majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = 7;
                            break;
                        case 1:
                            intervalAddition = 6;
                            break;
                        case 2:
                            intervalAddition = 5;
                            break;
                        case 3:
                            intervalAddition = 9;
                            break;
                        case 4:
                            intervalAddition = 8;
                            break;
                        case 5:
                            intervalAddition = 7;
                            break;
                        case 7:
                            intervalAddition = 9; // or 2?
                            break;
                        case 9:
                            intervalAddition = 7;
                            break;
                        case 11:
                            intervalAddition = 5;
                            break;
                    }
                }
                
                if (!majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = 9;
                            break;
                        case 1:
                            intervalAddition = 8;
                            break;
                        case 2:
                            intervalAddition = 7;
                            break;
                        case 3:
                            intervalAddition = 6;
                            break;
                        case 4:
                            intervalAddition = 8;
                            break;
                        case 5:
                            intervalAddition = 7;
                            break;
                        case 6:
                            intervalAddition = 6;
                            break;
                        case 7:
                            intervalAddition = 5; // or 2?
                            break;
                        case 8:
                            intervalAddition = 4; // or 2?
                            break;
                        case 9:
                            intervalAddition = 7;
                            break;
                        case 10:
                            intervalAddition = 6;
                            break;
                        case 11:
                            intervalAddition = 5;
                            break;
                    }
                }
                break;
            case 2:
                if (majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = -5;
                            break;
                        case 1:
                            intervalAddition = -6;
                            break;
                        case 2:
                            intervalAddition = -2;
                            break;
                        case 3:
                            intervalAddition = -3;
                            break;
                        case 4:
                            intervalAddition = -4;
                            break;
                        case 5:
                            intervalAddition = -1;
                            break;
                        case 7:
                            intervalAddition = -3; // or 2?
                            break;
                        case 9:
                            intervalAddition = -2;
                            break;
                        case 11:
                            intervalAddition = -4;
                            break;
                    }
                }
                
                if (!majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = -3;
                            break;
                        case 1:
                            intervalAddition = -1;
                            break;
                        case 2:
                            intervalAddition = -2;
                            break;
                        case 3:
                            intervalAddition = -3;
                            break;
                        case 4:
                            intervalAddition = -4;
                            break;
                        case 5:
                            intervalAddition = -1;
                            break;
                        case 6:
                            intervalAddition = -2;
                            break;
                        case 7:
                            intervalAddition = -3; // or 2?
                            break;
                        case 8:
                            intervalAddition = -4; // or 2?
                            break;
                        case 9:
                            intervalAddition = -5;
                            break;
                        case 10:
                            intervalAddition = -1;
                            break;
                        case 11:
                            intervalAddition = -2;
                            break;
                    }
                }
                break;
            case 1:
                if (majorOn)
                {
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = -8;
                            break;
                        case 1:
                            intervalAddition = -8;
                            break;
                        case 2:
                            intervalAddition = -7;
                            break;
                        case 3:
                            intervalAddition = -8;
                            break;
                        case 4:
                            intervalAddition = -9;
                            break;
                        case 5:
                            intervalAddition = -5;
                            break;
                        case 7:
                            intervalAddition = -7; // or 2?
                            break;
                        case 9:
                            intervalAddition = -5;
                            break;
                        case 11:
                            intervalAddition = -7;
                            break;
                    }
                }
                
                if (!majorOn)
                {
                    
                    switch(interNote)
                    {
                        case 0:
                            intervalAddition = -8;
                            break;
                        case 1:
                            intervalAddition = -4;
                            break;
                        case 2:
                            intervalAddition = -5;
                            break;
                        case 3:
                            intervalAddition = -6;
                            break;
                        case 4:
                            intervalAddition = -7;
                            break;
                        case 5:
                            intervalAddition = -5;
                            break;
                        case 6:
                            intervalAddition = -6;
                            break;
                        case 7:
                            intervalAddition = -7; // or 2?
                            break;
                        case 8:
                            intervalAddition = -8; // or 2?
                            break;
                        case 9:
                            intervalAddition = -9;
                            break;
                        case 10:
                            intervalAddition = -6;
                            break;
                        case 11:
                            intervalAddition = -7;
                            break;
                    }
                }
                break;
        }
        return intervalAddition;
    }
};
