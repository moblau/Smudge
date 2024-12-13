/*
  ==============================================================================

    SVerb.cpp
    Created: 12 Dec 2024 8:40:34am
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "SVerb.h"

SVerb::SVerb()
{
    writeIndex = 0;
    for (int i = 0; i < 4; i++){
        allPassFilters.add(juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>(0));
    }
    
}
void SVerb::prepare(double sampleRate, int maxDelaySamples){
    this->sampleRate = sampleRate;
    delayLine.setSize(2, sampleRate*2);
    delayLine.clear();
    for (int i = 0; i < 4; i++){
        allPassFilters[i].setMaximumDelayInSamples(sampleRate*5);
    }
}

void SVerb::setParams(float delayTimeMs, float feedback, int allPassDelay0,int allPassDelay1,int allPassDelay2,int allPassDelay3){
    this->delaySamples = (int) (delayTimeMs/1000*sampleRate);
    this->feedback = feedback;
    allPassDelay[0] = allPassDelay0;
    allPassDelay[1] = allPassDelay1;
    allPassDelay[2] = allPassDelay2;
    allPassDelay[3] = allPassDelay3;
    
}

float SVerb::process(float input, int channel)
{
    int readIndex = (writeIndex - delaySamples) % delayLine.getNumSamples();
    
    if (readIndex < 0)
    {
        readIndex+=delayLine.getNumSamples();
    }
//    DBG(writeIndex << " " << readIndex);
    float delayedSample = delayLine.getSample(channel, readIndex);
    float output = delayedSample*feedback + input;
    delayLine.setSample(channel, writeIndex, output);
    writeIndex = (writeIndex+1) % delayLine.getNumSamples();
    return output;

    
}
