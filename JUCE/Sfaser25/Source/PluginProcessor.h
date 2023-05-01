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
    
    //input stage
        Input_Data I_data;
        Mat_IN S_in;
    //shifting stage
        Shift_Data Sh_data;
        Mat_SH S_sh;
    //output stage
        Output_Data O_data;
        Mat_OUT S_out;
    
    
    //Output_Data O_data;
    
    juce::AudioFormatManager formatManager;
    juce::AudioBuffer<float> GetAudioBufferFromFile(juce::File file);
    float sample_rate = 192000;
};
