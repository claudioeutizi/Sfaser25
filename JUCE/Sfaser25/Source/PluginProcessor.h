/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <JuceHeader.h>
#include "inputStage.h"
#include "outputStage.h"
#include "shiftStage.h"

//==============================================================================
/**
*/
class Sfaser25AudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Sfaser25AudioProcessor();
    ~Sfaser25AudioProcessor() override;

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
    float getSpeed();
    void setSpeed(float speed);
    //==============================================================================

private:
    float speed;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sfaser25AudioProcessor)
    
    //juce::ScopedPointer<juce::AudioProcessorValueTreeState> state;
    
    float stage0 = 0;
    float stage1 = 0;
    float stage2 = 0;
    float stage3 = 0;
    float stage4 = 0;
    float output = 0;

    //input stage
        wavesIN initIN;
        Matrix4f S_in;
    //shifting stage
        wavesSTAGE initSTAGE1;
        wavesSTAGE initSTAGE2;
        wavesSTAGE initSTAGE3;
        wavesSTAGE initSTAGE4;
        Matrix8d S_stage;
    //output stage
        wavesOUT initOUT;
        Matrix6f S_out;
    
    
    //Output_Data O_data;
    juce::AudioFormatManager formatManager;
    juce::AudioBuffer<float> GetAudioBufferFromFile(juce::File file);
    float sample_rate = 192000;
};
