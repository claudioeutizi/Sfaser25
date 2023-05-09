/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "./GUI/FilmStripSlider.h"

//==============================================================================
Sfaser25AudioProcessorEditor::Sfaser25AudioProcessorEditor (Sfaser25AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
	onOffSwitch("onOffSwitch"), ledOnOff("onOffLed"), speedKnob("speedKnob"), speedKnobAttachment(audioProcessor.apvts, "SPEED", speedKnob)
{
	//background 
	backgroundImage = juce::ImageCache::getFromMemory(BinaryData::pedal_full_res_2k_cropped_scaled_png, BinaryData::pedal_full_res_2k_cropped_scaled_pngSize);

	//knob strip
	speedKnobStripImage = juce::ImageCache::getFromMemory(BinaryData::speedknobstrip_png, BinaryData::speedknobstrip_pngSize);

	//on off 
	addAndMakeVisible(onOffSwitch);
	onOffSwitch.addListener(this);
	onOffSwitch.setImages(false, true, true,
		juce::ImageCache::getFromMemory(BinaryData::onoffswitchup_png, BinaryData::onoffswitchup_pngSize), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000),
		juce::ImageCache::getFromMemory(BinaryData::onoffswitchdown_png, BinaryData::onoffswitchdown_pngSize), 1.000f, juce::Colour(0x00000000));

	//on off led
	addAndMakeVisible(ledOnOff);
	ledOnOff.setEnabled(false);
	ledOnOff.addListener(this);
	ledOnOff.setImages(false, true, true,
		juce::ImageCache::getFromMemory(BinaryData::onoffledoff_png, BinaryData::onoffledoff_pngSize), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000));

	//speed knob
	addAndMakeVisible(speedKnob);
	speedKnob.setAlpha(0.0f);
	speedKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
	speedKnob.setPopupDisplayEnabled(true, true, nullptr);
	speedKnob.setTextValueSuffix(" Hz");
	speedKnob.setRange(0.1, 10, 0.1);
	speedKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	speedKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 0, 0);
	speedKnob.addListener(this);

	//previousRate = audioProcessor.getRateHz();
	//speedKnob->setValue(audioProcessor.getRateHz());
	//speedKnob->setAlpha(0);
	// 
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(windowWidth, windowHeight);
}

Sfaser25AudioProcessorEditor::~Sfaser25AudioProcessorEditor()
{
}

//==============================================================================
void Sfaser25AudioProcessorEditor::paint(juce::Graphics& g)
{
	FilmStripSlider fssSpeed(&speedKnobStripImage, 100);

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawImage(backgroundImage, 0, 0, backgroundImage.getWidth(),
		backgroundImage.getHeight(), 0, 0, backgroundImage.getWidth(),
		backgroundImage.getHeight(), false);

	fssSpeed.drawFrame(g, windowWidth / 2 - knobWidth / 2, 29, knobWidth, knobHeight, speedKnob, audioProcessor.getSpeed());
}

void Sfaser25AudioProcessorEditor::resized()
{
	onOffSwitch.setBounds(windowWidth / 2 - switchWidth / 2, switchY, switchWidth, switchHeight);
	ledOnOff.setBounds(windowWidth / 2 - ledWidth / 2, ledY, ledWidth, ledHeight);
	speedKnob.setBounds(windowWidth / 2 - knobWidth / 2, knobY, knobWidth, knobHeight);
}

void Sfaser25AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	if (slider == &speedKnob)
	{
		audioProcessor.setSpeed((float)(slider->getValue()));
	}
}


void Sfaser25AudioProcessorEditor::buttonClicked(juce::Button* button)
{
	audioProcessor.setOnOff(this->getButtonState());
	if (button == &onOffSwitch)
	{
		if (!this->getButtonState()) {
			ledOnOff.setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffledon_png, BinaryData::onoffledon_pngSize), 2.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));
			this->setButtonState(true);
		}
		else {
			ledOnOff.setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffledoff_png, BinaryData::onoffledoff_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));
			this->setButtonState(false);
		}
	}
}

void Sfaser25AudioProcessorEditor::timerCallback()
{
	if (previousSpeed != audioProcessor.getSpeed())
	{
		repaint();
		previousSpeed = audioProcessor.getSpeed();
	}
}
