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

void Sfaser25AudioProcessor::setSpeed(float speed)
{
    apvts.getParameter("SPEED")->setValue(speed);
}
float Sfaser25AudioProcessor::getSpeed()
{
    return apvts.getParameter("SPEED")->getValue();
}
void Sfaser25AudioProcessor::setOnOff(bool onOff)
{
    apvts.getParameter("ONOFF")->setValue(onOff);
}
bool Sfaser25AudioProcessor::getOnOff()
{
    return apvts.getParameter("ONOFF")->getValue();
}

//==============================================================================
void Sfaser25AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    juce::ignoreUnused (samplesPerBlock);
    sample_rate = (int)sampleRate;

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

    //perchè devo fare x10? Gli arriva un valore sballato di un ordine di grandezza?
    speed = getSpeed()*10;
    rounded = round(sample_rate / speed);

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
  
    
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);

    auto* inputBufferL = buffer.getReadPointer(0);
    auto* inputBufferR = buffer.getReadPointer(1);

    if (apvts.getParameter("ONOFF")->getValue()) {

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
             channelDataL[sample] = inputBufferL[sample];
             channelDataR[sample] = inputBufferR[sample];
        }
    }
    else{
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {

            /*lfoValue = std::sin(2 * 3.14159 * speed * lfoIndex / sample_rate) * 0.15 + 3.25;*/
            lfoValue = 3.4;
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
                outputL = outputStage.outputStageSample(shiftStageOutput4, inputStageOutput, S_out, initOUT);
            }

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
                outputR = outputStage.outputStageSample(shiftStageOutput4, inputStageOutput, S_out, initOUT);
            }

            channelDataL[sample] = outputL * makeupGain;
            channelDataR[sample] = outputR * makeupGain;

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

juce::AudioProcessorValueTreeState::ParameterLayout Sfaser25AudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("SPEED", "Speed", 0.1f, 10.0f, 0.1f));
    layout.add(std::make_unique<juce::AudioParameterBool>("ONOFF", "OnOff", true));
    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Sfaser25AudioProcessor();
}
