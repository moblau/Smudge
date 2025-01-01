/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SVerb.h"
#include "Filter.h"

//==============================================================================
/**
*/
class SVerbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SVerbAudioProcessor();
    ~SVerbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState& getAPVTS();
    
//    void handleMidi(juce::MidiBuffer& midiMessages);

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    std::atomic<float> * delayTime;
    std::atomic<float> * feedback;
    
    std::atomic<float> * allPassDelay0;
    std::atomic<float> * allPassDelay1;
    std::atomic<float> * allPassDelay2;
    
    std::atomic<float> * distortion;
    
    juce::dsp::DryWetMixer<float> dryWet;
    
//    int notesOn[4] {-1,-1,-1,-1};

    
    Filter filter;
    juce::AudioProcessorValueTreeState apvts;
    
    
    SVerb SVerb;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SVerbAudioProcessor)
};
