/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SVerbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SVerbAudioProcessorEditor (SVerbAudioProcessor&);
    ~SVerbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SVerbAudioProcessor& audioProcessor;

    
    juce::Slider delayKnob;
    juce::Slider feedbackKnob;
    juce::Slider distortionKnob;
    juce::Slider highPassKnob;
    juce::Slider lowPassKnob;
    juce::Slider dryWetKnob;
    juce::Slider lowPassQKnob;
    juce::Slider highPassQKnob;
    juce::Slider freqGainKnob;
    juce::Slider freqQKnob;
    juce::Slider ratioKnob;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowPassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highPassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowPassQAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highPassQAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqQAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioAttachment;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SVerbAudioProcessorEditor)
    juce::Slider allPassDelaySlider[3];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> allPassDelaySliderAttachment[3];
    
};
