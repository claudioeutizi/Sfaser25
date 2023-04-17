/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Face90AudioProcessorEditor  : public juce::AudioProcessorEditor,
                          // listen to buttons
                          public juce::Button::Listener, 
                          // listen to sliders
                          public juce::Slider::Listener
{
public:
    Face90AudioProcessorEditor (Face90AudioProcessor&);
    ~Face90AudioProcessorEditor() override;
    void buttonClicked(juce::Button* btn) override;
    void sliderValueChanged (juce::Slider *slider) override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Face90AudioProcessor& audioProcessor;

    juce::ToggleButton led; 
    juce::Slider speedSlider;
    juce::ToggleButton onOffSwitch;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Face90AudioProcessorEditor)
};
