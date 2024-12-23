/*
  ==============================================================================

    Filter.h
    Created: 23 Dec 2024 8:00:12am
    Author:  Morris Blaustein

  ==============================================================================
*/


#include <JuceHeader.h>

#pragma once
class Filter
{
    
public:
    Filter(juce::AudioProcessorValueTreeState& apvts);
    float process(float sample, std::atomic<float> * distortion);
    void prepare(juce::dsp::ProcessSpec spec);
    
    void process(juce::dsp::ProcessContextReplacing<float> block, int* notesOn );
    
private:
    juce::AudioProcessorValueTreeState& params;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowPass, highPass;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> peak0, peak1, peak2, peak3;
    
    int sampleRate;
    float mapLogScale(float input, float inputMin, float inputMax, float outputMin, float outputMax);
    float ramp0, ramp1;
    juce::dsp::Gain<float> outputGain;
    
};

