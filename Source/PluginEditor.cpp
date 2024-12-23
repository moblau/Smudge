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
    setSize (512, 512);
    
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
    
    lowPassKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    lowPassKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    lowPassKnob.setRange(20.0,20000.0,20000);
    lowPassKnob.setValue(20000.0);
    addAndMakeVisible(lowPassKnob);
    lowPassAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lowPass", lowPassKnob));
    
    highPassKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    highPassKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    highPassKnob.setRange(20.0,20000.0,20);
    highPassKnob.setValue(20.0);
    addAndMakeVisible(highPassKnob);
    highPassAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "highPass", highPassKnob));
    
    lowPassQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    lowPassQKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    lowPassQKnob.setRange(1,50,.1);
    lowPassQKnob.setValue(1);
    addAndMakeVisible(lowPassQKnob);
    lowPassQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lowPassQ", lowPassQKnob));
    
    highPassQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    highPassQKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    highPassQKnob.setRange(1,50,.1);
    highPassQKnob.setValue(1);
    addAndMakeVisible(highPassQKnob);
    highPassQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "highPassQ", highPassQKnob));
    
    dryWetKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    dryWetKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    dryWetKnob.setRange(0.0,1.0,0.0);
    dryWetKnob.setValue(1.0);
    addAndMakeVisible(dryWetKnob);
    dryWetAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "dryWet", dryWetKnob));
    
    freqGainKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    freqGainKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    freqGainKnob.setRange(0.0,12.0,1.0);
    freqGainKnob.setValue(1.0);
    addAndMakeVisible(freqGainKnob);
    freqGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "freqGain", freqGainKnob));
    
    freqQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    freqQKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    freqQKnob.setRange(1.0,100.0,1.0);
    freqQKnob.setValue(1.0);
    addAndMakeVisible(freqQKnob);
    freqQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "freqQ", freqQKnob));
    
    ratioKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    ratioKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    ratioKnob.setRange(1.0,16.0,1.0);
    ratioKnob.setValue(1.0);
    addAndMakeVisible(ratioKnob);
    ratioAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "ratio", ratioKnob));
    
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
    auto topRatio = bounds.getWidth()/3;
    auto bottom = bounds.removeFromBottom(bounds.getHeight()/4);
    auto leftArea = bounds.removeFromLeft(topRatio);
    auto midArea = bounds.removeFromLeft(topRatio);
    auto rightArea = bounds;
    
//    for(int i = 0; i < 3; i ++){
//        auto leftTopArea = topArea.withTrimmedLeft(i * topArea.getWidth()/3).withWidth(topArea.getWidth()/3);
//        allPassDelaySlider[i].setBounds(leftTopArea);
//
//    }
    
    delayKnob.setBounds(leftArea);
    feedbackKnob.setBounds(midArea);
    distortionKnob.setBounds(rightArea);
    auto freqGainBounds = bottom.removeFromTop(bottom.getHeight()/3);
    auto w = freqGainBounds.getWidth()/3;
    freqGainKnob.setBounds(freqGainBounds.removeFromLeft(w));
    freqQKnob.setBounds(freqGainBounds.removeFromLeft(w));
    ratioKnob.setBounds(freqGainBounds);
    float bottomRatio = bottom.getWidth()/3;
    auto topLowpass = bottom.removeFromLeft(bottomRatio);
    highPassKnob.setBounds(topLowpass.removeFromTop(topLowpass.getHeight()/2));
    highPassQKnob.setBounds(topLowpass);
    auto topHighPass =bottom.removeFromLeft(bottomRatio);
    lowPassKnob.setBounds(topHighPass.removeFromTop(topHighPass.getHeight()/2));
    lowPassQKnob.setBounds(topHighPass);
    dryWetKnob.setBounds(bottom.removeFromLeft(bottomRatio));
    
}
