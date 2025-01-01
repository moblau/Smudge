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
    
    
    signalOrder.setLookAndFeel(&customSliderLookAndFeel);
    addAndMakeVisible(signalOrder);
    signalOrderAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.getAPVTS(), "signalOrder", signalOrder));
    
    
    delayKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    delayKnob.setLookAndFeel(&customSliderLookAndFeel);
    delayKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    delayKnob.setRange(0,1000,0);
    delayKnob.setValue(0);
    addAndMakeVisible(delayKnob);
    delayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "delay", delayKnob));
    
    
    feedbackKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    feedbackKnob.setLookAndFeel(&customSliderLookAndFeel);
    feedbackKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    feedbackKnob.setRange(0.0,1.0,0);
    feedbackKnob.setValue(0.0);
    addAndMakeVisible(feedbackKnob);
    feedbackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "feedback", feedbackKnob));
    
    distortionKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    distortionKnob.setLookAndFeel(&customSliderLookAndFeel);

    distortionKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    distortionKnob.setRange(1.0,100.0,0);
    distortionKnob.setValue(0.0);
    addAndMakeVisible(distortionKnob);
    distortionAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "distortion", distortionKnob));
    
    lowPassKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    lowPassKnob.setLookAndFeel(&customSliderLookAndFeel);
    lowPassKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lowPassKnob.setRange(20.0,20000.0,20000);
    lowPassKnob.setValue(20000.0);
    addAndMakeVisible(lowPassKnob);
    lowPassAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lowPass", lowPassKnob));
    
    highPassKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    highPassKnob.setLookAndFeel(&customSliderLookAndFeel);
    highPassKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    highPassKnob.setRange(20.0,20000.0,20);
    highPassKnob.setValue(20.0);
    addAndMakeVisible(highPassKnob);
    highPassAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "highPass", highPassKnob));
    
    lowPassQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    lowPassQKnob.setLookAndFeel(&customSliderLookAndFeel);

    lowPassQKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lowPassQKnob.setRange(1,50,.1);
    lowPassQKnob.setValue(1);
    addAndMakeVisible(lowPassQKnob);
    lowPassQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lowPassQ", lowPassQKnob));
    
    highPassQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    highPassQKnob.setLookAndFeel(&customSliderLookAndFeel);

    highPassQKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    highPassQKnob.setRange(1,50,.1);
    highPassQKnob.setValue(1);
    addAndMakeVisible(highPassQKnob);
    highPassQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "highPassQ", highPassQKnob));
    
    dryWetKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    dryWetKnob.setLookAndFeel(&customSliderLookAndFeel);

    dryWetKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    dryWetKnob.setRange(0.0,1.0,0.0);
    dryWetKnob.setValue(1.0);
    addAndMakeVisible(dryWetKnob);
    dryWetAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "dryWet", dryWetKnob));
    
    decayTimeLabel.setText("Decay Time", juce::dontSendNotification);
    decayTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayTimeLabel);
    
    spreadLabel.setText("Spread", juce::dontSendNotification);
    spreadLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(spreadLabel);
    
    distortionLabel.setText("Distortion", juce::dontSendNotification);
    distortionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(distortionLabel);
    
    dryWetLabel.setText("Dry/Wet", juce::dontSendNotification);
    dryWetLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(dryWetLabel);
    
    lpLabel.setText("Lowpass Filter", juce::dontSendNotification);
    lpLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lpLabel);
    
    hpLabel.setText("Highpass Filter", juce::dontSendNotification);
    hpLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(hpLabel);
    
    qLabel.setText("Q", juce::dontSendNotification);
    qLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(qLabel);
    
    freqLabel.setText("Freq", juce::dontSendNotification);
    freqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(freqLabel);
    
    signalOrderLabel.setText("Rev          Dist", juce::dontSendNotification);
    signalOrderLabel.setJustificationType(juce::Justification::centred);
    signalOrderLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(signalOrderLabel);
    
    
    
    
    
//    freqGainKnob.setSliderStyle(juce::Slider::LinearHorizontal);
//    freqGainKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
//    freqGainKnob.setRange(0.0,12.0,1.0);
//    freqGainKnob.setValue(1.0);
//    addAndMakeVisible(freqGainKnob);
//    freqGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "freqGain", freqGainKnob));
//
//    freqQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
//    freqQKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
//    freqQKnob.setRange(1.0,100.0,1.0);
//    freqQKnob.setValue(1.0);
//    addAndMakeVisible(freqQKnob);
//    freqQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "freqQ", freqQKnob));
//
//    ratioKnob.setSliderStyle(juce::Slider::LinearHorizontal);
//    ratioKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
//    ratioKnob.setRange(1.0,16.0,1.0);
//    ratioKnob.setValue(1.0);
//    addAndMakeVisible(ratioKnob);
//    ratioAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "ratio", ratioKnob));
    
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
    delayKnob.setLookAndFeel(nullptr);
    feedbackKnob.setLookAndFeel(nullptr);
    distortionKnob.setLookAndFeel(nullptr);
    lowPassKnob.setLookAndFeel(nullptr);
    highPassKnob.setLookAndFeel(nullptr);
    highPassQKnob.setLookAndFeel(nullptr);
    lowPassQKnob.setLookAndFeel(nullptr);
    dryWetKnob.setLookAndFeel(nullptr);
    signalOrder.setLookAndFeel(nullptr);

}

//==============================================================================
void SVerbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fill background with gradient from top to bottom
    juce::Rectangle<int> bounds = getLocalBounds();
    
    juce::ColourGradient gradient (juce::Colours::lightgrey, bounds.getX(), bounds.getY(),
                                   juce::Colours::darkgrey, bounds.getX(), bounds.getBottom(), false);
    gradient.multiplyOpacity(.2);
    g.setGradientFill(gradient);
    g.fillRect(bounds);  // Fill the entire component with the gradient
    title = juce::ImageCache::getFromMemory(BinaryData::tourniquet_png, BinaryData::tourniquet_pngSize  );
    g.drawImageWithin(title, 30, 0, 512 , 256, juce::RectanglePlacement::stretchToFit);
    lulubyLogo = juce::ImageCache::getFromMemory(BinaryData::luluby_png, BinaryData::luluby_pngSize  );
    g.drawImageWithin(lulubyLogo, 70, 25, 70 , 70, juce::RectanglePlacement::stretchToFit);
}

void SVerbAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds = bounds.reduced(15,15);
    auto topRatio = bounds.getWidth()/3;
    auto bottom = bounds.removeFromBottom(bounds.getHeight()/2);
    auto top = bounds.removeFromTop(topRatio/2);
    auto leftArea = bounds.removeFromLeft(topRatio);
    auto decayTimeArea = leftArea.removeFromBottom(25);
    auto midArea = bounds.removeFromLeft(topRatio);
    auto rightArea = bounds;
    auto spreadArea = midArea.removeFromBottom(25);
    auto distortionArea = rightArea.removeFromBottom(25);
    
//    for(int i = 0; i < 3; i ++){
//        auto leftTopArea = topArea.withTrimmedLeft(i * topArea.getWidth()/3).withWidth(topArea.getWidth()/3);
//        allPassDelaySlider[i].setBounds(leftTopArea);
//
//    }
    
    delayKnob.setBounds(leftArea.reduced(20, 20));
    decayTimeLabel.setBounds(decayTimeArea);
    feedbackKnob.setBounds(midArea.reduced(20, 20));
    spreadLabel.setBounds(spreadArea);
    distortionKnob.setBounds(rightArea.reduced(20, 20));
    distortionLabel.setBounds(distortionArea);
//    auto freqGainBounds = bottom.removeFromTop(bottom.getHeight()/3);
//    auto w = freqGainBounds.getWidth()/3;
//    freqGainKnob.setBounds(freqGainBounds.removeFromLeft(w));
//    freqQKnob.setBounds(freqGainBounds.removeFromLeft(w));
//    ratioKnob.setBounds(freqGainBounds);
    float bottomRatio = bottom.getWidth()/3;
    auto topLowpass = bottom.removeFromLeft(bottomRatio);
    auto lpLabelArea = topLowpass.removeFromBottom(25);
    lpLabel.setBounds(lpLabelArea);
    highPassKnob.setBounds(topLowpass.removeFromTop(topLowpass.getHeight()/2).reduced(10,10));
    highPassQKnob.setBounds(topLowpass.reduced(10,10));
    auto topHighPass =bottom.removeFromLeft(bottomRatio);
    auto hpLabelArea = topHighPass.removeFromBottom(25);
    hpLabel.setBounds(hpLabelArea);
    lowPassKnob.setBounds(topHighPass.removeFromTop(topHighPass.getHeight()/2).reduced(10,10));
    lowPassQKnob.setBounds(topHighPass.reduced(10,10));
    auto dryWetArea = bottom.removeFromLeft(bottomRatio).reduced(40, 40);
    auto signalOrderArea = dryWetArea.removeFromTop(50);
    signalOrderLabel.setBounds(365,310,100,20);
    signalOrder.setBounds(signalOrderArea);
    auto dryWetLabelArea = dryWetArea.removeFromBottom(25);
    dryWetKnob.setBounds(dryWetArea);
    dryWetLabel.setBounds(dryWetLabelArea);
    qLabel.setBounds(335, 408, 20, 20);
    freqLabel.setBounds(320,300,50,20);
    
    
}
