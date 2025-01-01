/*
  ==============================================================================

    SVerb.h
    Created: 12 Dec 2024 8:40:34am
    Author:  Morris Blaustein

  ==============================================================================
*/
#include <JuceHeader.h>
#include "Distortion.h"

#pragma once
class SVerb
{
public:
    SVerb(juce::AudioProcessorValueTreeState& apvts);
    void prepare(double sampleRate, int maxDelaySamples);
    void setParams(float delayTimeMs, float feedback, int allPassDelay0,int allPassDelay1,int allPassDelay2);
    float process(juce::AudioBuffer<float>& buffer, std::atomic<float> * delayTime, std::atomic<float> * feedback, std::atomic<float> * waveshaper);
    
private:
    juce::AudioBuffer<float> apf0delayLine;
    juce::AudioBuffer<float> apf1delayLine;
    juce::AudioBuffer<float> apf2delayLine;
    
    int writeIndex0, readIndex0;
    int writeIndex1, readIndex1;
    int writeIndex2, readIndex2;
    
    juce::AudioBuffer<float> cf3delayLine;
    juce::AudioBuffer<float> cf4delayLine;
    juce::AudioBuffer<float> cf5delayLine;
    juce::AudioBuffer<float> cf6delayLine;
    
    juce::dsp::DelayLine<float> line1;
    juce::dsp::DelayLine<float> line2;
    juce::dsp::DelayLine<float> line3;
    
    juce::dsp::DelayLine<float> line4;
    juce::dsp::DelayLine<float> line5;
    juce::dsp::DelayLine<float> line6;
    juce::dsp::DelayLine<float> line7;
    
    int writeIndex3, readIndex3;
    int writeIndex4, readIndex4;
    int writeIndex5, readIndex5;
    int writeIndex6, readIndex6;
    
    int allPassDelay[3];
    float feedback;
    double sampleRate;
    
    int apDelay1, apDelay2, apDelay3;
    int cfDelay1, cfDelay2, cfDelay3, cfDelay4;
    
    juce::dsp::DelayLine<float> apf0, apf1, apf2;
    juce::AudioProcessorValueTreeState& params;
    Distortion distortion;
    float decay;

    
};

