/*
  ==============================================================================

    Transport.h
    Created: 30 Oct 2022 7:55:01pm
    Author:  Mouldy Soul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct Transport
{
    void prepare(double sampleRate, int maxBlockSize)
    {
        samplesInMinute = sampleRate * 60;
        ppqPositions.resize(maxBlockSize);
    }
    
    double getPPQPerSample()
    {
        auto samplesPerBeat = samplesInMinute / info.bpm;
        return 1.0 / samplesPerBeat;
    }
    
    void process(juce::AudioPlayHead* playhead, int numSamples)
    {
        if (playhead != nullptr)
        {
            playhead->getCurrentPosition(info);
        }
        
        auto ppqPerSample = getPPQPerSample();
        double offset = 0.0;
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            ppqPositions[sample] = info.ppqPosition + offset;
            offset += ppqPerSample;
        }
    }
    double samplesInMinute = 0.0;
    juce::AudioPlayHead::CurrentPositionInfo info;
    std::vector<double> ppqPositions;
    
};
