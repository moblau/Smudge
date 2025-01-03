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
    Distortion(juce::AudioProcessorValueTreeState& apvts);
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer);
private:
    juce::dsp::WaveShaper<float> waveshaper;
    juce::dsp::Gain<float> inputGain, outputGain;
    std::unique_ptr<juce::dsp::Oversampling<float>> oversampling;
    juce::AudioProcessorValueTreeState& params;

    
};

