/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 May 2010 3:31:21pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_AUDIODEMOPLAYBACKPAGE_AUDIODEMOPLAYBACKPAGE_EA8C85BF__
#define __JUCER_HEADER_AUDIODEMOPLAYBACKPAGE_AUDIODEMOPLAYBACKPAGE_EA8C85BF__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AudioDemoPlaybackPage  : public Component,
                               public FileBrowserListener,
                               public ButtonListener,
                               public SliderListener
{
public:
    //==============================================================================
    AudioDemoPlaybackPage (AudioDeviceManager& deviceManager_);
    ~AudioDemoPlaybackPage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Label* zoomLabel;
    DemoThumbnailComp* thumbnail;
    TextButton* startStopButton;
    FileTreeComponent* fileTreeComp;
    Slider* zoomSlider;
    Slider* timeScaleSlider_;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    AudioDemoPlaybackPage (const AudioDemoPlaybackPage&);
    const AudioDemoPlaybackPage& operator= (const AudioDemoPlaybackPage&);
};


#endif   // __JUCER_HEADER_AUDIODEMOPLAYBACKPAGE_AUDIODEMOPLAYBACKPAGE_EA8C85BF__
