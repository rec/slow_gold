/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  10 Apr 2010 8:13:13pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

//[Headers]     -- You can add your own extra header files here --

#include "MainPageK.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.
                                                                    //[/Comments]
*/
class MainPageJ  : public Component,
                   public ButtonListener,
                   public SliderListener
{
public:
    //==============================================================================
    MainPageJ (AudioDeviceManager& deviceManager_);
    ~MainPageJ();

  void paint (Graphics& g);
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void sliderValueChanged (Slider* sliderThatWasMoved);
  void selectionChanged();


    //==============================================================================
    juce_UseDebuggingNewOperator

  private:
  //[UserVariables]   -- You can add your own custom variables in this section.
  MainPageK peer_;
  friend class MainPageK;

 public:
  void loadRecentFile(int menuItemId) { peer_.loadRecentFile(menuItemId); }

 private:

  //[/UserVariables]

    //==============================================================================
    Label* zoomLabel;
    rec::gui::AudioThumbnailComponent* thumbnail;
    TextButton* startStopButton;
    FileTreeComponent* fileTreeComp;
    Label* explanation;
    Slider* zoomSlider;
    Slider* timeScaleSlider;
    Slider* pitchScaleSlider;
    ToggleButton* loopingButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainPageJ(const MainPageJ&);
    const MainPageJ& operator= (const MainPageJ&);
};


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
