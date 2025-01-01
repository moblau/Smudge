/*
  ==============================================================================

    Filter.cpp
    Created: 23 Dec 2024 8:00:12am
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "Filter.h"
Filter::Filter(juce::AudioProcessorValueTreeState& apvts) :
                    params(apvts),
                    lowPass(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100.f, 20000.f)),
                    highPass(juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(44100.f, 20.f)),
                    peak0(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1)),
                    peak1(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1)),
                    peak2(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1)),
                    peak3(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1))

{
//    ramp0 = 1;
//    ramp1 = .1;
}

void Filter::prepare(juce::dsp::ProcessSpec spec)
{
    sampleRate = spec.sampleRate;
    lowPass.prepare(spec);
    highPass.prepare(spec);
//    peak0.prepare(spec);
//    peak1.prepare(spec);
//    peak2.prepare(spec);
//    peak3.prepare(spec);
    
}

void Filter::process(juce::dsp::ProcessContextReplacing<float> block )
{
    
    float lowPassFreq = *params.getRawParameterValue("lowPass");
    float highPassFreq = *params.getRawParameterValue("highPass");
    float lowQ = *params.getRawParameterValue("lowPassQ");;
    float highQ = *params.getRawParameterValue("highPassQ");;
    *lowPass.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowPassFreq, lowQ);
    *highPass.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highPassFreq, highQ);
    
//    float freqGain = *params.getRawParameterValue("freqGain");
//    float freqQ = *params.getRawParameterValue("freqQ");
//    float ratio = *params.getRawParameterValue("ratio");;
//    DBG(ratio << "  " << notesOn[0]);
//    if( notesOn[0] != -1 ){
//        *peak0.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, juce::MidiMessage::getMidiNoteInHertz(notesOn[0])*ratio, freqQ, freqGain);
//        ramp0=1;
////        if (freqGain*ramp0<freqGain ||freqQ*ramp0<freqQ ){
////            ramp1 += .001;
////        }
//    }
//    else{
//        if (freqGain*ramp0>1 ||freqQ*ramp0>1 ){
//            ramp0 -= .01;
//        }
//
//        *peak0.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, freqQ*ramp0, freqGain*ramp0);
//    }
//    if( notesOn[1] != -1 ){
//        *peak1.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, juce::MidiMessage::getMidiNoteInHertz(notesOn[1])*ratio, freqQ, freqGain);
//    }
//    else{
//        *peak1.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1);
//    }
//    if( notesOn[2] != -1 ){
//        *peak2.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, juce::MidiMessage::getMidiNoteInHertz(notesOn[2])*ratio, freqQ, freqGain);
//    }
//    else{
//        *peak2.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1);
//    }
//    if( notesOn[3] != -1 ){
//        *peak3.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, juce::MidiMessage::getMidiNoteInHertz(notesOn[3])*ratio, freqQ, freqGain);
//    }
//    else{
//        *peak3.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 100, 1, 1);
//    }
    
    
    lowPass.process(block);
    
//    peak0.process(block);
//
//    peak1.process(block);
//
//    peak2.process(block);
//
//    peak3.process(block);
    
    highPass.process(block);
    
//    outputGain.setGainLinear(1);
    
//    outputGain.process(block);
    
    
    
}
