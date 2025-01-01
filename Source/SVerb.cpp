/*
  ==============================================================================

    SVerb.cpp
    Created: 12 Dec 2024 8:40:34am
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "SVerb.h"

SVerb::SVerb(juce::AudioProcessorValueTreeState& apvts) : params(apvts)
{
    
}
void SVerb::prepare(double sampleRate, int samplesPerBlock){
    
//    apDelay1 = (int) (0.347*sampleRate*44/25);
//    apDelay2 = (int) (0.113*sampleRate*44/25);
//    apDelay3 = (int) (0.37*sampleRate*44/25);
//
//    cfDelay1 = (int) (1.687*sampleRate*44/25);
//    cfDelay2 = (int) (1.601*sampleRate*44/25);
//    cfDelay3 = (int) (2.053*sampleRate*44/25);
//    cfDelay4 = (int) (2.251*sampleRate*44/25);
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    
    apDelay1 = (int)(347);
    apDelay2 = (int)(113);
    apDelay3 = (int)(37);

    cfDelay1 = (int)(1687);
    cfDelay2 = (int)(1601);
    cfDelay3 = (int)(2053);
    cfDelay4 = (int)(2251);
//
    line1.prepare(spec);
    line1.reset();
    line1.setMaximumDelayInSamples(sampleRate*4);
    
    line2.prepare(spec);
    line2.reset();
    line2.setMaximumDelayInSamples(sampleRate*4);
    
    line3.prepare(spec);
    line3.reset();
    line3.setMaximumDelayInSamples(sampleRate*4);
    
    line4.prepare(spec);
    line4.reset();
    line4.setMaximumDelayInSamples(sampleRate*4);
    
    line5.prepare(spec);
    line5.reset();
    line5.setMaximumDelayInSamples(sampleRate*4);
    
    line6.prepare(spec);
    line6.reset();
    line6.setMaximumDelayInSamples(sampleRate*4);

    line7.prepare(spec);
    line7.reset();
    line7.setMaximumDelayInSamples(sampleRate*4);

//    cfDelay1 = (int)(20000);
//    cfDelay2 = (int)(11200);
//    cfDelay3 = (int)(13700);
//    cfDelay4 = (int)(9100);
//    writeIndex0 = 0;
//    writeIndex1 = 0;
//    writeIndex2 = 0;
//    writeIndex3 = 0;
//    writeIndex4 = 0;
//    writeIndex5 = 0;
//    writeIndex6 = 0;
////    this->sampleRate = sampleRate;
//    apf0delayLine.setSize(2, apDelay1);
//    apf0delayLine.clear();
//
//
//    apf1delayLine.setSize(2, apDelay2);
//    apf1delayLine.clear();
//
//    apf2delayLine.setSize(2, apDelay3);
//    apf2delayLine.clear();
//
//
//
//    cf3delayLine.setSize(2, cfDelay1);
//    cf3delayLine.clear();
//    cf4delayLine.setSize(2, cfDelay2);
//    cf4delayLine.clear();
//    cf5delayLine.setSize(2, cfDelay3);
//    cf5delayLine.clear();
//    cf6delayLine.setSize(2, cfDelay4);
//    cf6delayLine.clear();

    
    
//    juce::dsp::ProcessSpec spec;
//    spec.sampleRate = sampleRate;
//    spec.maximumBlockSize = samplesPerBlock;
//    spec.numChannels = 2;
//
//    apf0.prepare(spec);
//    apf0.reset();
//    apf0.setMaximumDelayInSamples(sampleRate);
//
//    apf1.prepare(spec);
//    apf1.reset();
//    apf1.setMaximumDelayInSamples(sampleRate);
//
//    apf2.prepare(spec);
//    apf2.reset();
//    apf2.setMaximumDelayInSamples(sampleRate);
}

void SVerb::setParams(float delayTimeMs, float feedback, int allPassDelay0,int allPassDelay1,int allPassDelay2){
    decay = feedback;

}

float SVerb::process(juce::AudioBuffer<float>& buffer, std::atomic<float> * delayTime, std::atomic<float> * feedback,std::atomic<float> * waveshaper)
{

//
//
    
    float delayCaptured;
    float feedbackCaptured;
    int signalOrder;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for ( int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            signalOrder = *params.getRawParameterValue("signalOrder");
            if (signalOrder == 1){
                channelData[sample] = distortion.process(channelData[sample], waveshaper);
            }
            delayCaptured = delayTime->load();
            feedbackCaptured = feedback->load();
            line1.setDelay(apDelay1+delayCaptured);
            line2.setDelay(apDelay2+delayCaptured*(1+feedbackCaptured));
            line3.setDelay(apDelay3+delayCaptured*(1+feedbackCaptured*3));
            line4.setDelay(cfDelay1+delayCaptured*(1+feedbackCaptured*5));
            line5.setDelay(cfDelay2+delayCaptured*(1+feedbackCaptured*7));
            line6.setDelay(cfDelay3+delayCaptured*(1+feedbackCaptured*11));
            line7.setDelay(cfDelay4+delayCaptured*(1+feedbackCaptured*13));
            float inputSample = channelData[sample];
            setParams(0, .7, 0, 0, 0);
            
            float a=.7;
            
//            readIndex0 = writeIndex0 - apDelay1;
            
//            if ( readIndex0 < 0){
//                readIndex0+= apf0delayLine.getNumSamples();
//            }
//
//            float v_delayed = apf0delayLine.getSample(channel, writeIndex0);
//            DBG("read " << readIndex0 << " " << v_delayed);
            float v_delayed = line1.popSample(channel);
            float output = a*inputSample + v_delayed;
            float new_v = inputSample - a*v_delayed;
            line1.pushSample(channel, new_v);
            
            float temp = output;
            v_delayed = line2.popSample(channel);
            output = a*output + v_delayed;
            new_v = temp - a*v_delayed;
            line2.pushSample(channel, new_v);
//
            temp = output;
            v_delayed = line3.popSample(channel);
            output = a*output + v_delayed;
            new_v = temp - a*v_delayed;
            line3.pushSample(channel, new_v);
            
            temp = output;
            float out1, out2, out3, out4;
            
            v_delayed = line4.popSample(channel);
            out1 = temp + a*v_delayed;
            line4.pushSample(channel, temp);
            
            v_delayed = line5.popSample(channel);
            out2 = temp + a*v_delayed;
            line5.pushSample(channel, temp);
            
            v_delayed = line6.popSample(channel);
            out3 = temp + a*v_delayed;
            line6.pushSample(channel, temp);
            
            v_delayed = line7.popSample(channel);
            out4 = temp + a*v_delayed;
            line7.pushSample(channel, temp);
            
            
            
            output = (out1+out2+out3+out4)/4;
            if (signalOrder == 0){
                output = distortion.process(output, waveshaper);
            }
            
            channelData[sample] = output;
            //            v_delayed= cf3delayLine.getSample(channel, readIndex3);
            //            out1 = tempOut + a*v_delayed;
            //            writeIndex3 = (writeIndex3+1) % cf3delayLine.getNumSamples();
            //            cf3delayLine.setSample(channel, writeIndex3, output);
            
            
            //            apf0delayLine.setSample(channel, writeIndex0, new_v);
            //            writeIndex0 = (writeIndex0+1) % apf0delayLine.getNumSamples();
//
//            readIndex1 = writeIndex1 - apDelay2 +1;
//            if ( readIndex1 < 0){
//                readIndex1+= apf1delayLine.getNumSamples();
//            }
//            float tempOut = output;
//            v_delayed = apf1delayLine.getSample(channel, writeIndex1);
//            output = a*output + v_delayed;
//            new_v = tempOut - a*output;
//            writeIndex1 = (writeIndex1) % apf1delayLine.getNumSamples();
//            apf1delayLine.setSample(channel, writeIndex1, new_v);
//
//        //
//        //
//        //
//            readIndex2 = writeIndex2 - apDelay3 +1;
//            if ( readIndex2 < 0){
//                readIndex2+= apf2delayLine.getNumSamples();
//            }
//
//            tempOut = output;
//            v_delayed = apf2delayLine.getSample(channel, readIndex2);
//            output = a*output + v_delayed;
//            new_v = tempOut - a*output;
//            writeIndex2 = (writeIndex2+1) % apf2delayLine.getNumSamples();
//            apf2delayLine.setSample(channel, writeIndex2, new_v);
//
//            tempOut = output;
//            float out1,out2,out3,out4;
//            a = .773;
//
//            readIndex3 = writeIndex3 - cfDelay1 +1;
//            if ( readIndex3 < 0){
//                readIndex3+= cf3delayLine.getNumSamples();
//            }
//
//            v_delayed= cf3delayLine.getSample(channel, readIndex3);
//            out1 = tempOut + a*v_delayed;
//            writeIndex3 = (writeIndex3+1) % cf3delayLine.getNumSamples();
//            cf3delayLine.setSample(channel, writeIndex3, output);
//
//
//
//            a = .802;
//            readIndex4 = writeIndex4 - cfDelay2 +1;
//            if ( readIndex4 < 0){
//                readIndex4+= cf4delayLine.getNumSamples();
//            }
//            v_delayed= cf4delayLine.getSample(channel, readIndex4);
//            out2 = tempOut + a*v_delayed;
//            writeIndex4 = (writeIndex4+1) % cf4delayLine.getNumSamples();
//            cf4delayLine.setSample(channel, writeIndex4, output);
//
//
//
//            a = .753;
//            readIndex5 = writeIndex5 - cfDelay3 +1;
//            if ( readIndex5 < 0){
//                readIndex5+= cf5delayLine.getNumSamples();
//            }
//            v_delayed= cf5delayLine.getSample(channel, readIndex5);
//            out3 = tempOut + a*v_delayed;
//            writeIndex5 = (writeIndex5+1) % cf5delayLine.getNumSamples();
//            cf5delayLine.setSample(channel, writeIndex5, output);
//
//
//
//            a = .773;
//            readIndex6 = writeIndex6 - cfDelay4 +1;
//            if ( readIndex6 < 0){
//                readIndex6+= cf6delayLine.getNumSamples();
//            }
//            v_delayed= cf6delayLine.getSample(channel, readIndex6);
//            out4 = tempOut + a*v_delayed;
//            writeIndex6 = (writeIndex6+1) % cf6delayLine.getNumSamples();
//            cf6delayLine.setSample(channel, writeIndex6, output);
//

//
//            channelData[sample] = (out1+out2+out3+out4)*.25;
            
        }
    }
    
    


    
}
