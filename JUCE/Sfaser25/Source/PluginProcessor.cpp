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
                       )
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    juce::ignoreUnused (sampleRate, samplesPerBlock);

        //Compute S for each stage
        S_in = PrepareInputStage(sample_rate);
        S_stage = PrepareShiftStage(sample_rate);
        S_out = PrepareOutputStage(sample_rate);
        //juce::File inputFile("C:/Users/matti/Desktop/MAE/mxrPhase90/Face90/MATLAB/Sfaser25/ExpSweep.wav");
        //juce::File outputFile("C:/Users/matti/Desktop/MAE/mxrPhase90/Face90/MATLAB/Sfaser25/outputSweep.wav");

        //juce::AudioFormatManager formatManager;
        //formatManager.registerBasicFormats();

        //juce::AudioFormatReader* reader = formatManager.createReaderFor(inputFile);
        //if (reader != nullptr)
        //{
        //    // Read the audio data from the input file
        //    juce::AudioBuffer<float> buffer(reader->numChannels, reader->lengthInSamples);
        //    reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);


        //    juce::AudioBuffer<float> buffer2(reader->numChannels, reader->lengthInSamples);

        //    // Process the audio data here...
        //    auto* inputBuffer = buffer.getReadPointer(0);
        //    auto* outputBuffer = buffer2.getWritePointer(0);

        //    for (int sample = 0; sample < buffer.getNumSamples()-1; ++sample)
        //    {
        //        const float input_sample = inputBuffer[sample];

        //        stage0 = InputStageSample(input_sample, S_in, initIN);
        //        stage1 = ShiftStageSample(stage0, S_stage, initSTAGE);
        //        stage2 = ShiftStageSample(stage1, S_stage, initSTAGE);
        //        stage3 = ShiftStageSample(stage2, S_stage, initSTAGE);
        //        stage4 = ShiftStageSample(stage3, S_stage, initSTAGE);
        //        output = OutputStageSample(stage4, stage0, S_out, initOUT);

        //        outputBuffer[sample] = output * 3;
        //    }

        //    // Create a new audio file for the output
        //    juce::FileOutputStream outputStream(outputFile);
        //    if (outputStream.openedOk())
        //    {
        //        juce::WavAudioFormat wavFormat;
        //        std::unique_ptr<juce::AudioFormatWriter> writer(
        //            wavFormat.createWriterFor(&outputStream, reader->sampleRate, reader->numChannels, 16, {}, 0)
        //        );;
        //        if (writer != nullptr)
        //        {
        //            // Write the processed audio data to the output file
        //            writer->writeFromAudioSampleBuffer(buffer2, 0, buffer2.getNumSamples());
        //        }
        //    }

        //    // Clean up the reader
        //    delete reader;
        //}
}

//juce native - based method found online
juce::AudioBuffer<float> Sfaser25AudioProcessor::GetAudioBufferFromFile(juce::File file)
{
    auto* reader = formatManager.createReaderFor(file);
    juce::AudioBuffer<float> audioBuffer;
    audioBuffer.setSize(reader->numChannels, reader->lengthInSamples);
    reader->read(&audioBuffer, 0, reader->lengthInSamples, 0, true, true);
    delete reader;
    return audioBuffer;
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

    
    auto totalNumInputChannels  = 1; //getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());

     int channel = 0;
     auto* channelData = buffer.getWritePointer (channel);
     auto* channelData1 = buffer.getWritePointer (channel+1);


    float input_out = 0;
    float makeupGain = 3;



       //sample by sample computation
       auto inputBuffer = buffer.getReadPointer(channel);//MONO input

       for(int sample = 0; sample<buffer.getNumSamples(); ++sample)
       {
           const float input_sample = inputBuffer[sample];

           stage0 = InputStageSample(input_sample, S_in, initIN);
           stage1 = ShiftStageSample(stage0, S_stage, initSTAGE1);
           stage2 = ShiftStageSample(stage1, S_stage, initSTAGE2);
           stage3 = ShiftStageSample(stage2, S_stage, initSTAGE3);
           stage4 = ShiftStageSample(stage3, S_stage, initSTAGE4);
           output = OutputStageSample(stage4, stage0, S_out, initOUT);
           
           channelData[sample] = output * makeupGain;
           channelData1[sample] = channelData[sample];
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
    return this->speed;
}

void Sfaser25AudioProcessor::setSpeed(float speed)
{
    this->speed = speed;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Sfaser25AudioProcessor();
}
