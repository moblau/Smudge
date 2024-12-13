/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SVerbAudioProcessor::SVerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "PARAMETERS", createParameters())
#endif
{
    delayTime = apvts.getRawParameterValue("delay");
    feedback = apvts.getRawParameterValue("feedback");
    allPassDelay0 = apvts.getRawParameterValue("allPassDelay0");
    allPassDelay1 = apvts.getRawParameterValue("allPassDelay1");
    allPassDelay2 = apvts.getRawParameterValue("allPassDelay2");
    allPassDelay3 = apvts.getRawParameterValue("allPassDelay3");
}

SVerbAudioProcessor::~SVerbAudioProcessor()
{
}

//==============================================================================
const juce::String SVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SVerbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void SVerbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    SVerb.prepare(sampleRate, sampleRate);
}

void SVerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SVerbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for ( int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            SVerb.setParams(delayTime->load(), feedback->load(),allPassDelay0->load(),allPassDelay1->load(),allPassDelay2->load(),allPassDelay3->load());
            float inputSample = channelData[sample];
            float output = SVerb.process(inputSample, channel);
            channelData[sample] = output;
        }
    }
    DBG(allPassDelay0->load() << " " << allPassDelay1->load() << " " <<allPassDelay2->load() << " " <<allPassDelay3->load());
}

//==============================================================================
bool SVerbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SVerbAudioProcessor::createEditor()
{
    return new SVerbAudioProcessorEditor (*this);
}

//==============================================================================
void SVerbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SVerbAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SVerbAudioProcessor::createParameters()
{

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    parameters.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID("delay",1),"delay",0,1000,0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("feedback",1),"feedback",0.0,1.0,0.0));
    for ( int i = 0; i < 4; i++){
        auto paramName = "allPassDelay" + juce::String(i);
        parameters.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID(paramName,1),paramName,0.0,1000.0,1.0));
    }
    return {parameters.begin(), parameters.end()};
    
}

juce::AudioProcessorValueTreeState& SVerbAudioProcessor::getAPVTS()
{
    return apvts;
}
