/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TimeStampAudioProcessor::TimeStampAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TimeStampAudioProcessor::~TimeStampAudioProcessor()
{
}

//==============================================================================
const juce::String TimeStampAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TimeStampAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TimeStampAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TimeStampAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TimeStampAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TimeStampAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TimeStampAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TimeStampAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TimeStampAudioProcessor::getProgramName (int index)
{
    return {};
}

void TimeStampAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TimeStampAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    delayVoice.prepare(sampleRate, samplesPerBlock); // this prepares the transport function in delay voice
}

void TimeStampAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TimeStampAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TimeStampAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    jassert (buffer.getNumChannels() == 0);
    
    delayVoice.process(buffer, midiMessages, getPlayHead(), 0.5, 1, false,true, midiBuff,true,12,true,0,0);
    // This is not a great way of doing things, it's sample accurate timing, but so many edge cases, that this method now needs to go.
    
    // I've been reading and instead of using Juce's midi buffer, I need to make my own midi buffer, and mutate/change time stamps in there, then swap with midi buffer at the end.
}

//==============================================================================
bool TimeStampAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TimeStampAudioProcessor::createEditor()
{
    return new TimeStampAudioProcessorEditor (*this);
}

//==============================================================================
void TimeStampAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TimeStampAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TimeStampAudioProcessor();
}
