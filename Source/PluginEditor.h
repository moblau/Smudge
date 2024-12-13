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
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SVerbAudioProcessorEditor)
    juce::Slider allPassDelaySlider[4];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> allPassDelaySliderAttachment[4];
    
};
