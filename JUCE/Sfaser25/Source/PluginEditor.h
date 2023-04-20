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
class Sfaser25AudioProcessorEditor : public juce::AudioProcessorEditor,
    juce::Button::Listener,
    juce::Slider::Listener,
	juce::Timer
{
public:
    Sfaser25AudioProcessorEditor (Sfaser25AudioProcessor&);
    ~Sfaser25AudioProcessorEditor() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* btn) override;
	void timerCallback() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
	void setButtonState(bool buttonState) { this->buttonState = buttonState; };
	bool getButtonState() { return this->buttonState; };

private:
	float previousSpeed = 0;
	bool onOffSwitchPressed = false;
	bool repaintFlag = false;

	juce::Image speedKnobStripImage;
	juce::Image backgroundImage;
	juce::Image onOffSwitchStripImage;

	Sfaser25AudioProcessor& audioProcessor;
	juce::ScopedPointer<juce::Slider> speedKnob;

	juce::ScopedPointer<juce::ImageButton> onOffSwitch;
	bool buttonState = false;

	juce::ScopedPointer<juce::ImageButton> ledOnOff;

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


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sfaser25AudioProcessorEditor)
};
