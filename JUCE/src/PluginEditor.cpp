/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Face90AudioProcessorEditor::Face90AudioProcessorEditor (Face90AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(speedSlider);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setRange(0.1, 10, 0.1);
    speedSlider.addListener(this);

    addAndMakeVisible(led);
    led.addListener(this);

    addAndMakeVisible(onOffSwitch);
    onOffSwitch.addListener(this);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Face90AudioProcessorEditor::~Face90AudioProcessorEditor()
{
}

//==============================================================================
void Face90AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Face90AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void buttonClicked(juce::Button* btn){
}


void sliderValueChanged (juce::Slider *slider){
}
