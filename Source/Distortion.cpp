/*
  ==============================================================================

    Distortion.cpp
    Created: 21 Dec 2024 10:44:49pm
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion() : waveshaper{{std::tanh}}
{
    
}

float Distortion::process(float sample, std::atomic<float> * distortion)
{
    float dist = distortion->load();
    inputGain.setGainLinear(dist);
    outputGain.setGainLinear(1/dist*100);
    float output = inputGain.processSample(sample);
    output = waveshaper.processSample(output);
    output = outputGain.processSample(output);
    return output;
}
