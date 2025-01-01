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
                       ), apvts(*this, nullptr, "PARAMETERS", createParameters()),
                            filter(apvts), SVerb(apvts)
#endif
{
    delayTime = apvts.getRawParameterValue("delay");
    feedback = apvts.getRawParameterValue("feedback");
    allPassDelay0 = apvts.getRawParameterValue("allPassDelay0");
    allPassDelay1 = apvts.getRawParameterValue("allPassDelay1");
    allPassDelay2 = apvts.getRawParameterValue("allPassDelay2");
    distortion = apvts.getRawParameterValue("distortion");
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
    SVerb.prepare(sampleRate, samplesPerBlock);
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    
    spec.numChannels = 2;
    dryWet.prepare(spec);
    filter.prepare(spec);
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
//    handleMidi(midiMessages);
    dryWet.pushDrySamples(buffer);
    dryWet.setWetMixProportion(*apvts.getRawParameterValue("dryWet"));
    juce::dsp::AudioBlock<float> block(buffer);
    
    
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
    SVerb.process(buffer,delayTime, feedback, distortion);
    
    
    dryWet.mixWetSamples(buffer);
    
    

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
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void SVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
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
    parameters.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID("delay",1),"delay",0,2500,0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("feedback",1),"feedback",0.0,1.0,0.0));
    for ( int i = 0; i < 3; i++){
        auto paramName = "allPassDelay" + juce::String(i);
        parameters.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID(paramName,1),paramName,0.0,44100.0,1.0));
    }
    parameters.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID("distortion",1),"distortion",1,100,0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lowPass",1),"lowPass",juce::NormalisableRange<float>(20, 20000, .1, .2),20000));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("highPass",1),"highPass",juce::NormalisableRange<float>(20, 20000, .1, .2),20));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("dryWet",1),"dryWet",0,1,1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lowPassQ",1),"lowPassQ",juce::NormalisableRange<float>(1, 25, .1),1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("highPassQ",1),"highPassQ",juce::NormalisableRange<float>(1, 25, .1),1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("freqGain",1),"freqGain",juce::NormalisableRange<float>(1, 12, .1),1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("freqQ",1),"freqQ",juce::NormalisableRange<float>(1, 25, .1),1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("ratio",1),"ratio",juce::NormalisableRange<float>(1, 16, 1),1));
    parameters.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID("signalOrder",1),"signalOrder",0,1,0));
    
    return {parameters.begin(), parameters.end()};
    
}

juce::AudioProcessorValueTreeState& SVerbAudioProcessor::getAPVTS()
{
    return apvts;
}

//void SVerbAudioProcessor::handleMidi(juce::MidiBuffer& midiMessages)
//{
//    juce::MidiBuffer::Iterator it(midiMessages);
//    juce::MidiMessage message;
//    int samplePos;
//    
//    while (it.getNextEvent(message,samplePos))
//    {
//        if (message.isNoteOn())
//        {
//            for ( int i = 0; i < 4; i ++){
//                if (notesOn[i] == -1){
//                    notesOn[i] = message.getNoteNumber();
//                    break;
//                }
//            }
//        }
//        if (message.isNoteOff())
//        {
//            for ( int i = 0; i < 4; i ++){
//                if (message.getNoteNumber()==notesOn[i]){
//                    notesOn[i] = -1;
//                    break;
//                }
//            }
//        }
//        
//    }
//}
