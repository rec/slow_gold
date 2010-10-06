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

#include "rec/slow/app/MainPageK.h"
#include "rec/widget/Time.h"

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
  rec::slow::MainPageK peer_;
  friend class rec::slow::MainPageK;

  void sliderDragEnded(Slider* slider);

 public:
  void loadRecentFile(int menuItemId) { peer_.loadRecentFile(menuItemId); }
  void cut() { peer_.cut(); }
  void paste() { peer_.paste(); }

 private:

  //[/UserVariables]

    //==============================================================================
    Label* zoomLabel;
    rec::widget::AudioThumbnailWidget* thumbnail;
    TextButton* startStopButton;
    FileTreeComponent* fileTreeComp;
    Label* explanation;
    Slider* zoomSlider;
    Slider* timeScaleSlider;
    Slider* pitchScaleSlider;
    ToggleButton* loopingButton;
    rec::widget::time::TextComponent* songTime;
    rec::widget::time::TextComponent* realTime;
    rec::widget::time::DialComponent* songDial;
    rec::widget::time::DialComponent* realDial;
    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainPageJ(const MainPageJ&);
    const MainPageJ& operator= (const MainPageJ&);
};


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
