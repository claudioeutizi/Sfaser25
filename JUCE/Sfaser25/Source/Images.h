/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Images: public juce::Component,
    public juce::Button::Listener
{
public:
    //==============================================================================
    Images();
    ~Images();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    // Binary resources:
    static char* croppedPedal_png;
    static const int croppedPedal_pngSize = 2714990;
    //static const char* croppedPedal_png2;
    //static const int croppedPedal_png2Size;
    static char* ledOff_png;
    static const int ledOff_pngSize = 63598;
    static char* ledOn_png;
    static const int ledOn_pngSize = 61217;
    static char* onOffSwitchDown_png;
    static const int onOffSwitchDown_pngSize = 157869;
    static char* onOffSwitchUp_png;
    static const int onOffSwitchUp_pngSize = 156319;
    static char* switch_left_png;
    static char* speedKnobFilmRoll_png;
    static const int speedKnobFilmRoll_pngSize = 4177142;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ImageButton> imageButton4;
    juce::Image cachedImage_croppedPedal_png2_1;
    juce::Image cachedImage_ledOff_png_2;
    juce::Image cachedImage_ledOn_png_3;
    juce::Image cachedImage_onOffSwitchDown_png_4;
    juce::Image cachedImage_onOffSwitchUp_png_5;
    juce::Image cachedImage_speedKnobFilmRoll_png_8;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Images)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
