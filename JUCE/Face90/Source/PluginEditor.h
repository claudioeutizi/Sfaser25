/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FilmStripSlider.h"
#include "Images.h"

//==============================================================================
/**
*/
class Face90AudioProcessorEditor : public juce::AudioProcessorEditor,
    juce::Button::Listener,
    juce::Slider::Listener,
	juce::Timer
{
public:
    Face90AudioProcessorEditor (Face90AudioProcessor&);
    ~Face90AudioProcessorEditor() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* btn) override;
	void timerCallback() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	float previousSpeed = 0;
	bool onOffSwitchPressed = false;
	bool repaintFlag = false;

	juce::Image cachedImage_speedKnobFilmRoll_png_1;
	juce::Image cachedImage_BaseModel_png_1;
	juce::Image cachedImage_ledOff_png_1;
	juce::Image cachedImage_ledOn_png_2;
	juce::Image cachedImage_onOffSwitchDown_png_5;
	juce::Image cachedImage_onOffSwitchUp_png2_6;

	Face90AudioProcessor& audioProcessor;
	juce::ScopedPointer<juce::Slider> speedKnob;
	juce::ScopedPointer<juce::ImageButton> onOffSwitch;
	juce::ScopedPointer<juce::ImageButton> ledOnOff;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Face90AudioProcessorEditor)
};
