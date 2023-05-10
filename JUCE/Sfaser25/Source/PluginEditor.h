/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/Sfaser25LookAndFeel.h"

//==============================================================================
/**
*/
class Sfaser25AudioProcessorEditor : public juce::AudioProcessorEditor,
    juce::Button::Listener,
	juce::Timer
{
public:
    Sfaser25AudioProcessorEditor (Sfaser25AudioProcessor&);
    ~Sfaser25AudioProcessorEditor() override;
    void buttonClicked(juce::Button* btn) override;
	void timerCallback() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	float previousSpeed = 0;
	bool previousState = true;
	bool repaintFlag = false;

	SpeedKnobLookAndFeel speedKnobLookAndFeel;
	MixKnobLookAndFeel mixKnobLookAndFeel;
	juce::Image speedKnobStripImage, backgroundImage, ledOnImage, ledOffImage;

	juce::Slider speedKnob;
	juce::Slider mixKnob;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixKnobAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedKnobAttachment;

	juce::ImageButton onOffSwitch;

	juce::ImageButton ledOnOff;

	const int windowWidth = 360;
	const int windowHeight = 497;

	const int knobY = 29;
	const int knobWidth = 118;
	const int knobHeight = 135;	

	const int ledY = 163;
	const int ledWidth = 138;
	const int ledHeight = 134;	

	const int switchY = 284;
	const int switchWidth = 146;
	const int switchHeight = 164;

	Sfaser25AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sfaser25AudioProcessorEditor)
};
