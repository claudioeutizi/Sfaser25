/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#pragma once

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
Sfaser25AudioProcessor::Sfaser25AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), inputStage(), shiftStage(), outputStage(), apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
}

Sfaser25AudioProcessor::~Sfaser25AudioProcessor()
{
}

//==============================================================================
const juce::String Sfaser25AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Sfaser25AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Sfaser25AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Sfaser25AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Sfaser25AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Sfaser25AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Sfaser25AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Sfaser25AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Sfaser25AudioProcessor::getProgramName (int index)
{
    return {};
}

void Sfaser25AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Sfaser25AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    juce::ignoreUnused (samplesPerBlock);
    sample_rate = (int)sampleRate;
    //internalSampleRate = sampleRate;
    //oversamplingFactor = log2(sample_rate / internalSampleRate);

    //oversampling(channels, oversamplingFactor, juce::dsp::Oversampling<float>::FilterType::filterHalfBandFIREquiripple);
    
    //Compute S for each stage

    S_in = inputStage.prepareInputStage(sample_rate);
    shiftStage.prepareShiftStage(sample_rate);
    S_out = outputStage.prepareOutputStage(sample_rate);


}

void Sfaser25AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Sfaser25AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Sfaser25AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;


    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    float speed = getSpeed();

    rounded = round(sample_rate / speed);

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
  
    
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);

    auto* inputBufferL = buffer.getReadPointer(0);
    auto* inputBufferR = buffer.getReadPointer(1);

    if (!getOnOffState()) {

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
             channelDataL[sample] = inputBufferL[sample];
             channelDataR[sample] = inputBufferR[sample];
        }
    }

    else {

        dryWetParam = getMix();
        dry = 1.0f - dryWetParam;
        wet = dryWetParam;


        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
           
            if (speed!=speedOld) {
                lfoIndex = lfoIndex*speedOld/speed;
            }

            speedOld = speed;
            //lfoValue = 2 * 0.3 * std::abs(speed * lfoIndex / sample_rate - floor(speed * lfoIndex / sample_rate + 0.5)) + 3.1;
            lfoValue = LFO((float)(lfoIndex * speed) / sample_rate);
            //lfoValue = std::sin(lfoIndex * 2 * 3.1415 * speed / sample_rate) * 0.15 + 3.25;
         
           
            drySampleL = inputBufferL[sample] * dry;

            input_sample = inputBufferL[sample];

            if (!input_sample) {
                outputL = 0;
            }
            else {
                inputStageOutput = inputStage.inputStageSample(input_sample, S_in, initIN);
                shiftStageOutput1 = shiftStage.shiftStageSample(inputStageOutput, initSTAGE1L, lfoValue);
                shiftStageOutput2 = shiftStage.shiftStageSample(shiftStageOutput1, initSTAGE2L, lfoValue);
                shiftStageOutput3 = shiftStage.shiftStageSample(shiftStageOutput2, initSTAGE3L, lfoValue);
                shiftStageOutput4 = shiftStage.shiftStageSample(shiftStageOutput3, initSTAGE4L, lfoValue);
                outputL = (outputStage.outputStageSample(shiftStageOutput4, inputStageOutput, S_out, initOUT)-1e-4);
            }

            
            drySampleR = inputBufferR[sample] * dry;

            input_sample = inputBufferR[sample];

            if (!input_sample) {
                outputR = 0;
            }
            else {

                inputStageOutput = inputStage.inputStageSample(input_sample, S_in, initIN);
                shiftStageOutput1 = shiftStage.shiftStageSample(inputStageOutput, initSTAGE1R, lfoValue);
                shiftStageOutput2 = shiftStage.shiftStageSample(shiftStageOutput1, initSTAGE2R, lfoValue);
                shiftStageOutput3 = shiftStage.shiftStageSample(shiftStageOutput2, initSTAGE3R, lfoValue);
                shiftStageOutput4 = shiftStage.shiftStageSample(shiftStageOutput3, initSTAGE4R, lfoValue);
                outputR = (outputStage.outputStageSample(shiftStageOutput4, inputStageOutput, S_out, initOUT)-1e-4);
            }

            
            wetSampleL = outputL * wet;
            wetSampleR = outputR * wet;

            //output somma dei segnali dry/wet
            channelDataL[sample] = (drySampleL + wetSampleL * makeupGain);
            channelDataR[sample] = (drySampleR + wetSampleR * makeupGain);

            lfoIndex++;

            lfoIndex = lfoIndex % rounded;
        }


    }
 }
    


//==============================================================================
bool Sfaser25AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Sfaser25AudioProcessor::createEditor()
{
    return new Sfaser25AudioProcessorEditor (*this);
}

//==============================================================================
void Sfaser25AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    }

void Sfaser25AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
}

float Sfaser25AudioProcessor::getSpeed()
{
    auto& speedValue = *apvts.getRawParameterValue("SPEED");
    return speedValue;
}

float Sfaser25AudioProcessor::getMix()
{
    auto& speedValue = *apvts.getRawParameterValue("MIX");
    return speedValue;
}


float Sfaser25AudioProcessor::LFO(float index) {
    if (index < dutyCycle) {
        return (index*0.3) / dutyCycle + 3.1;
    }
    else {
        return 0.3 / (1 - dutyCycle)*(-index + 1) + 3.1;
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout Sfaser25AudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //Speed Parameter
    juce::NormalisableRange<float> speedRange = juce::NormalisableRange<float>(0.1f, 10.f, 0.005f);
    speedRange.setSkewForCentre(2.5f);
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SPEED", "Speed", speedRange, 0.1f, "Hz"));

    //Dry Wet Parameter
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", juce::NormalisableRange<float>(0.f, 1.f, 0.0005f), 1.f));

    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Sfaser25AudioProcessor();
}

