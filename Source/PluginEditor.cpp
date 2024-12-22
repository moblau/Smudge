/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SVerbAudioProcessorEditor::SVerbAudioProcessorEditor (SVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    delayKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    delayKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    delayKnob.setRange(0,1000,0);
    delayKnob.setValue(0);
    addAndMakeVisible(delayKnob);
    delayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "delay", delayKnob));
    
    feedbackKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    feedbackKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    feedbackKnob.setRange(0.0,1.0,0);
    feedbackKnob.setValue(0.0);
    addAndMakeVisible(feedbackKnob);
    feedbackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "feedback", feedbackKnob));
    
    distortionKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    distortionKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    distortionKnob.setRange(1.0,100.0,0);
    distortionKnob.setValue(0.0);
    addAndMakeVisible(distortionKnob);
    distortionAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "distortion", distortionKnob));
    
//    for ( int i = 0; i < 3; i ++){
//        allPassDelaySlider[i].setSliderStyle(juce::Slider::RotaryVerticalDrag);
//        allPassDelaySlider[i].setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
//        allPassDelaySlider[i].setRange(0,44100,0);
//        allPassDelaySlider[i].setValue(0);
//        addAndMakeVisible(allPassDelaySlider[i]);
//        allPassDelaySliderAttachment[i].reset(new juce::AudioProcessorValueTreeState::SliderAttachment( audioProcessor.getAPVTS(), "allPassDelay" + juce::String(i), allPassDelaySlider[i]));
//    }
}

SVerbAudioProcessorEditor::~SVerbAudioProcessorEditor()
{
}

//==============================================================================
void SVerbAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void SVerbAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto leftArea = bounds.removeFromLeft(bounds.getWidth()/3);
    auto midArea = bounds.removeFromLeft(bounds.getWidth()/3);
    auto rightArea = bounds;
    
//    for(int i = 0; i < 3; i ++){
//        auto leftTopArea = topArea.withTrimmedLeft(i * topArea.getWidth()/3).withWidth(topArea.getWidth()/3);
//        allPassDelaySlider[i].setBounds(leftTopArea);
//
//    }
    
    delayKnob.setBounds(leftArea);
    feedbackKnob.setBounds(midArea);
    distortionKnob.setBounds(rightArea);
    
    
}
