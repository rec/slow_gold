/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Apr 2010 10:55:59pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_AUDIODEMOPLAYBACKPAGE_AUDIODEMOPLAYBACKPAGE_FD83EAC0__
#define __JUCER_HEADER_AUDIODEMOPLAYBACKPAGE_AUDIODEMOPLAYBACKPAGE_FD83EAC0__

//[Headers]     -- You can add your own extra header files here --
#include "JuceLibraryCode/JuceHeader.h"
#include "MainPageK.h"
#include "AudioThumbnailComponent.h"
#include "rec/base/scoped_ptr.h"
#include "rec/audio/source/Stretchable.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class FileBrowserPage  : public Component,
                               public FileBrowserListener,
                               public ButtonListener,
                               public SliderListener
{
public:
    //==============================================================================
    FileBrowserPage (AudioDeviceManager& deviceManager_);
    ~FileBrowserPage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    // These methods are our FileBrowserListener implementation:
    void selectionChanged();
  void fileClicked (const File& file, const MouseEvent& e) {}
  void fileDoubleClicked (const File& file) {}
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    friend class MainPageK;
    MainPageK peer_;

    AudioDeviceManager& deviceManager;
    TimeSliceThread thread;
    DirectoryContentsList directoryList;

    AudioTransportSource transportSource;

    AudioFormatReaderSource* currentAudioFileSource;
    scoped_ptr<rec::audio::source::Stretchable> transportSourceWrapper;
    AudioSourcePlayer audioSourcePlayer;
    void loadFileIntoTransport (const File& audioFile);

    //[/UserVariables]

    //==============================================================================
    Label* zoomLabel;
    rec::AudioThumbnailComponent* thumbnail;
    TextButton* startStopButton;
    FileTreeComponent* fileTreeComp;
    Label* explanation;
    Slider* zoomSlider;
    ToggleButton* loopingButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    FileBrowserPage (const FileBrowserPage&);
    const FileBrowserPage& operator= (const FileBrowserPage&);
};


#endif   // __JUCER_HEADER_AUDIODEMOPLAYBACKPAGE_AUDIODEMOPLAYBACKPAGE_FD83EAC0__
