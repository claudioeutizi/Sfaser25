/*
  ==============================================================================

    Sfaser25LookAndFeel.cpp
    Created: 9 May 2023 12:30:02pm
    Author:  claud

  ==============================================================================
*/

#include "Sfaser25LookAndFeel.h"

Sfaser25LookAndFeel::Sfaser25LookAndFeel() 
{
    speedKnobStripImage = ImageCache::getFromMemory(BinaryData::speedknobstrip_png, BinaryData::speedknobstrip_pngSize);
    speedKnobStripFrames = speedKnobStripImage.getHeight() / knobHeight;
}

Sfaser25LookAndFeel::~Sfaser25LookAndFeel() 
{
}

// ==========================================================================================================================

void Sfaser25LookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    if (speedKnobStripImage.isValid()) {

        auto imageIndex = int(sliderPos * speedKnobStripFrames);
        const int frameId = jlimit(0, speedKnobStripFrames - 1, imageIndex);
        const float radiusWidth = width / 2.0f;
        const float radiusHeight = height / 2.0f;
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radiusWidth;
        const float ry = centerY - radiusHeight;

        g.drawImage(speedKnobStripImage, rx, ry, knobWidth, knobHeight, 0, frameId * (speedKnobStripImage.getHeight() / speedKnobStripFrames), knobWidth, knobHeight);
    }
    else {
        static const float textPpercent = 0.35f;
        juce::Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(juce::Colours::white);

        g.drawFittedText(juce::String("No Image"), text_bounds.getSmallestIntegerContainer(),
            juce::Justification::horizontallyCentred | juce::Justification::centred, 1);
    }
}
