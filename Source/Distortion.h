/*
  ==============================================================================

    Distortion.h
    Created: 21 Dec 2024 10:44:49pm
    Author:  Morris Blaustein

  ==============================================================================
*/
#include <JuceHeader.h>

#pragma once
class Distortion
{
    
public:
    Distortion();
    float process(float sample, std::atomic<float> * distortion);
private:
    juce::dsp::WaveShaper<float> waveshaper;
    juce::dsp::Gain<float> inputGain, outputGain;
    
};

