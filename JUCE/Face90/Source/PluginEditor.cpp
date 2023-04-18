/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FilmStripSlider.h"

//==============================================================================
Face90AudioProcessorEditor::Face90AudioProcessorEditor (Face90AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	cachedImage_BaseModel_png_1 = juce::ImageCache::getFromMemory(BinaryData::GUI_cropped_png, BinaryData::GUI_cropped_pngSize);
	cachedImage_speedKnobFilmRoll_png_1 = juce::ImageCache::getFromMemory(BinaryData::speed_knob_png, BinaryData::speed_knob_pngSize);

	//on off switch
	addAndMakeVisible(onOffSwitch = new juce::ImageButton("onoffswitch"));
	onOffSwitch->addListener(this);
	onOffSwitch->setImages(false, true, true,
		juce::ImageCache::getFromMemory(BinaryData::onoffswitch0015_png, BinaryData::onoffswitch0015_pngSize), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000));

	//on off led
	addAndMakeVisible(ledOnOff = new juce::ImageButton("onoffLed"));
	ledOnOff->addListener(this);
	ledOnOff->setImages(false, true, true,
		juce::ImageCache::getFromMemory(BinaryData::onoffled0074_png, BinaryData::onoffled0074_pngSize), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000));

	//speed knob
	addAndMakeVisible(speedKnob = new juce::Slider("SKnob"));
	speedKnob->setRange(0, 1, 0.01);
	speedKnob->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	speedKnob->setTextBoxStyle(juce::Slider::TextBoxLeft, false, 0, 0);
	speedKnob->addListener(this);
	//previousRate = audioProcessor.getRateHz();
	//speedKnob->setValue(audioProcessor.getRateHz());
	//speedKnob->setAlpha(0);
	// 
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(616, 925);
}

Face90AudioProcessorEditor::~Face90AudioProcessorEditor()
{
	onOffSwitch = nullptr;
	ledOnOff = nullptr;
	speedKnob = nullptr;
}

//==============================================================================
void Face90AudioProcessorEditor::paint(juce::Graphics& g)
{
	FilmStripSlider fssSpeed(&cachedImage_speedKnobFilmRoll_png_1, 100);

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawImage(cachedImage_BaseModel_png_1, 0, 0, cachedImage_BaseModel_png_1.getWidth(),
		cachedImage_BaseModel_png_1.getHeight(), 0, 0, cachedImage_BaseModel_png_1.getWidth(), 
		cachedImage_BaseModel_png_1.getHeight(), false);

	if (repaintFlag == true) {

		if (onOffSwitchPressed == true)
		{
			ledOnOff->setBounds(256, 495, 103, 106);
			ledOnOff->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffled0075_png, BinaryData::onoffled0075_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));

			onOffSwitch->setBounds(225, 630, 166, 169);
			onOffSwitch->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffswitch0017_png, BinaryData::onoffswitch0017_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));
			repaintFlag = false;
		}

		else
		{
			ledOnOff->setBounds(256, 495, 103, 106);
			ledOnOff->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffled0074_png, BinaryData::onoffled0074_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));

			onOffSwitch->setBounds(225, 630, 166, 169);
			onOffSwitch->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffswitch0015_png, BinaryData::onoffswitch0015_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));
			repaintFlag = false;
		}
	}
	fssSpeed.drawFrame(g, 214, 100, 188, 183, *speedKnob, audioProcessor.getSpeed());
}

void Face90AudioProcessorEditor::resized()
{
	onOffSwitch->setBounds(225, 630, 166, 169);
	ledOnOff->setBounds(256, 495, 103, 106);
	speedKnob->setBounds(214, 100, 188, 183);
}

void Face90AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	if (slider == speedKnob)
	{
		audioProcessor.setSpeed((float)(slider->getValue()));
	}
}


void Face90AudioProcessorEditor::buttonClicked(juce::Button* button)
{


	if (button == onOffSwitch)
	{
		repaintFlag = true;
		onOffSwitchPressed = !onOffSwitchPressed;
		//audioProcessor.enablePedal(footSwitchPressed);
	}
}

void Face90AudioProcessorEditor::timerCallback()
{
	if (previousSpeed != audioProcessor.getSpeed())
	{
		repaint();
		previousSpeed = audioProcessor.getSpeed();
	}
}
