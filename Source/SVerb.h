/*
  ==============================================================================

    SVerb.h
    Created: 12 Dec 2024 8:40:34am
    Author:  Morris Blaustein

  ==============================================================================
*/
#include <JuceHeader.h>

#pragma once
class SVerb
{
public:
    SVerb();
    void prepare(double sampleRate, int maxDelaySamples);
    void setParams(float delayTimeMs, float feedback, int allPassDelay0,int allPassDelay1,int allPassDelay2,int allPassDelay3);
    float process(float input, int channel);
    
private:
    juce::AudioBuffer<float> delayLine;
    int writeIndex, delaySamples;
    int allPassDelay[4];
    float feedback;
    double sampleRate;
    
    juce::Array<juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>> allPassFilters;


    
};

