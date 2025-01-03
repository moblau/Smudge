/*
  ==============================================================================

    Distortion.cpp
    Created: 21 Dec 2024 10:44:49pm
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion(juce::AudioProcessorValueTreeState& apvts) : waveshaper{{std::tanh}},
    oversampling(std::make_unique<juce::dsp::Oversampling<float>>(2, 4, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR)),
    params(apvts)
{
}

void Distortion::prepare(const juce::dsp::ProcessSpec& spec)
{
    oversampling->reset();
    oversampling->initProcessing(spec.maximumBlockSize);
}

void Distortion::process(juce::AudioBuffer<float>& buffer)
{
    float dist = *params.getRawParameterValue("distortion");
    inputGain.setGainLinear(dist);
    outputGain.setGainLinear(1/sqrt(dist));
    
    juce::dsp::AudioBlock<float> block(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    inputGain.process(context);
    auto oversampledBlock = oversampling->processSamplesUp(context.getInputBlock());
    
//    auto waveshaperContext = juce::dsp::ProcessContextReplacing<float>(oversampledBlock);
    waveshaper.process(context);
    
    oversampling->processSamplesDown(context.getOutputBlock());
    outputGain.process(context);
    
//    oversampling->processSamplesDown(oversampledBlock);

}
