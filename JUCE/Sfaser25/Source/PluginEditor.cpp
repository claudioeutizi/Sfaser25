/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FilmStripSlider.h"

//==============================================================================
Sfaser25AudioProcessorEditor::Sfaser25AudioProcessorEditor (Sfaser25AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	cachedImage_BaseModel_png_1 = juce::ImageCache::getFromMemory(BinaryData::pedal_full_res_2k_cropped_scaled_png, BinaryData::pedal_full_res_2k_cropped_scaled_pngSize);
	cachedImage_speedKnobFilmRoll_png_1 = juce::ImageCache::getFromMemory(BinaryData::speedknobstrip_png, BinaryData::speedknobstrip_pngSize);

	//on off switch
	addAndMakeVisible(onOffSwitch = new juce::ImageButton("onOffSwitch"));
	onOffSwitch->addListener(this);
	onOffSwitch->setImages(false, true, true,
		juce::ImageCache::getFromMemory(BinaryData::onoffswitchup_png, BinaryData::onoffswitchup_pngSize), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000));

	//on off led
	addAndMakeVisible(ledOnOff = new juce::ImageButton("onOffLed"));
	ledOnOff->addListener(this);
	ledOnOff->setImages(false, true, true,
		juce::ImageCache::getFromMemory(BinaryData::onoffledoff_png, BinaryData::onoffledoff_pngSize), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000),
		juce::Image(), 1.000f, juce::Colour(0x00000000));

	//speed knob
	addAndMakeVisible(speedKnob = new juce::Slider("SpeedKnob"));
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
	setSize(windowWidth, windowHeight);
}

Sfaser25AudioProcessorEditor::~Sfaser25AudioProcessorEditor()
{
	onOffSwitch = nullptr;
	ledOnOff = nullptr;
	speedKnob = nullptr;
}

//==============================================================================
void Sfaser25AudioProcessorEditor::paint(juce::Graphics& g)
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
			ledOnOff->setBounds(windowWidth/2 - ledWidth/2, ledY, ledWidth, ledHeight);
			ledOnOff->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffledon_png, BinaryData::onoffledon_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));

			onOffSwitch->setBounds(windowWidth/2 - switchWidth/2, switchY, switchWidth, switchHeight);
			onOffSwitch->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffswitchdown_png, BinaryData::onoffswitchdown_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));
			repaintFlag = false;
		}

		else
		{
			ledOnOff->setBounds(windowWidth / 2 - ledWidth / 2, ledY, ledWidth, ledHeight);
			ledOnOff->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffledoff_png, BinaryData::onoffledoff_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));

			onOffSwitch->setBounds(windowWidth / 2 - switchWidth / 2, switchY, switchWidth, switchHeight);
			onOffSwitch->setImages(false, true, true,
				juce::ImageCache::getFromMemory(BinaryData::onoffswitchup_png, BinaryData::onoffswitchup_pngSize), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000),
				juce::Image(), 1.000f, juce::Colour(0x00000000));
			repaintFlag = false;
		}
	}
	fssSpeed.drawFrame(g, windowWidth / 2 - knobWidth / 2, 29, knobWidth, knobHeight, *speedKnob, audioProcessor.getSpeed());
}

void Sfaser25AudioProcessorEditor::resized()
{
	onOffSwitch->setBounds(windowWidth / 2 - switchWidth / 2, switchY, switchWidth, switchHeight);
	ledOnOff->setBounds(windowWidth / 2 - ledWidth / 2, ledY, ledWidth, ledHeight);
	speedKnob->setBounds(windowWidth / 2 - knobWidth / 2, knobY, knobWidth, knobHeight);
}

void Sfaser25AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	if (slider == speedKnob)
	{
		audioProcessor.setSpeed((float)(slider->getValue()));
	}
}


void Sfaser25AudioProcessorEditor::buttonClicked(juce::Button* button)
{


	if (button == onOffSwitch)
	{
		repaintFlag = true;
		onOffSwitchPressed = !onOffSwitchPressed;
		//audioProcessor.enablePedal(footSwitchPressed);
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
