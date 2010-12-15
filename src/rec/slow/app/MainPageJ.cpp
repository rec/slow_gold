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

#include "MainPageK.h"
#include "rec/widget/status/Time.pb.h"
#include "rec/widget/tree/Root.h"

using namespace juce;
using namespace rec::widget::tree;


#include "MainPageJ.h"

MainPageJ::MainPageJ(AudioDeviceManager& deviceManager)
:     peer_(&deviceManager),
      zoomLabel (0),
      waveform (0),
      startStopButton (0),
      treeTreeComp (0),
      explanation (0),
      zoomSlider (0),
      timeScaleSlider (0),
      loopingButton (0),
      songTime (0),
      realTime (0),
      songDial (0),
      realDial (0)
{
    addAndMakeVisible (zoomLabel = new Label (String::empty,
                                              T("zoom:")));
    zoomLabel->setFont (Font (15.0000f, Font::plain));
    zoomLabel->setJustificationType (Justification::centredRight);
    zoomLabel->setEditable (false, false, false);
    zoomLabel->setColour (TextEditor::textColourId, Colours::black);
    zoomLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (waveform = new rec::widget::waveform::Waveform(
        rec::widget::WaveformProto()));

    addAndMakeVisible (startStopButton = new TextButton (String::empty));
    startStopButton->setButtonText (T("Play/Stop"));
    startStopButton->addButtonListener (this);
    startStopButton->setColour (TextButton::buttonColourId, Colour (0xff79ed7f));

    addAndMakeVisible (treeTreeComp = new Root(NodeDesc()));
    addAndMakeVisible (explanation = new Label (String::empty,
                                                T("Select an audio file in the treeview above.")));
    explanation->setFont (Font (14.0000f, Font::plain));
    explanation->setJustificationType (Justification::bottomRight);
    explanation->setEditable (false, false, false);
    explanation->setColour (TextEditor::textColourId, Colours::black);
    explanation->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (zoomSlider = new Slider (String::empty));
    zoomSlider->setRange (0, 1, 0);
    zoomSlider->setSliderStyle (Slider::LinearHorizontal);
    zoomSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    zoomSlider->addListener (this);
    zoomSlider->setSkewFactor (2);

    addAndMakeVisible (loopingButton = new ToggleButton (T("looping button")));
    loopingButton->setButtonText (T("Loop sample?"));
    loopingButton->addButtonListener (this);
    loopingButton->setToggleState (true, false);

    addAndMakeVisible (timeScaleSlider = new Slider (T("Time Scale")));
    timeScaleSlider->setTooltip (T("Drag this to set the slowdown."));
    timeScaleSlider->setRange (0.5, 5, 0);
    timeScaleSlider->setSliderStyle (Slider::LinearHorizontal);
    timeScaleSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    timeScaleSlider->addListener (this);

    addAndMakeVisible (pitchScaleSlider = new Slider (T("Pitch Scale")));
    pitchScaleSlider->setTooltip (T("Drag this to set the pitchscale."));
    pitchScaleSlider->setRange (0.125, 4, 0);
    pitchScaleSlider->setSliderStyle (Slider::LinearHorizontal);
    pitchScaleSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    pitchScaleSlider->addListener (this);

    using rec::widget::status::time::TextComponent;
    using rec::widget::status::time::Text;
    using rec::gui::Colors;

    addAndMakeVisible(songTime = new TextComponent(Text()));
    addAndMakeVisible(realTime = new TextComponent(Text()));

    using rec::widget::status::time::DialComponent;
    using rec::widget::status::time::Dial;
    using rec::gui::Colors;

    Dial dial;
    addAndMakeVisible(songDial = new DialComponent(dial));

    Colors* colors = dial.mutable_widget()->mutable_colors();
    colors->add_color()->set_argb(Colours::white.getARGB());
    colors->add_color()->set_argb(Colours::green.getARGB());
    colors->add_color()->set_argb(Colours::red.getARGB());
    addAndMakeVisible(realDial = new DialComponent(dial));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
    peer_.construct(this);
    //[/Constructor]
}

MainPageJ::~MainPageJ()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
  peer_.destruct();
    //[/Destructor_pre]

    deleteAndZero (zoomLabel);
    deleteAndZero (waveform);
    deleteAndZero (startStopButton);
    deleteAndZero (treeTreeComp);
    deleteAndZero (explanation);
    deleteAndZero (zoomSlider);
    deleteAndZero (loopingButton);
    deleteAndZero (timeScaleSlider);
    deleteAndZero (pitchScaleSlider);
    deleteAndZero (songTime);
    deleteAndZero (realTime);
    deleteAndZero (songDial);
    deleteAndZero (realDial);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainPageJ::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainPageJ::resized()
{
    zoomLabel->setBounds (16, getHeight() - 90, 55, 24);
    waveform->setBounds (16, getHeight() - 221, getWidth() - 32, 123);
    startStopButton->setBounds (16, getHeight() - 46, 150, 32);
    treeTreeComp->setBounds (16, 8, getWidth() - 32, getHeight() - 245);
    explanation->setBounds (224, getHeight() - 42, getWidth() - 248, 32);
    zoomSlider->setBounds (72, getHeight() - 90, 200, 24);
    loopingButton->setBounds (192, getHeight() - 40, 150, 24);
    timeScaleSlider->setBounds (300, getHeight() - 90, 200, 24);
    pitchScaleSlider->setBounds (300, getHeight() - 60, 200, 24);
    songTime->setBounds (520, getHeight() - 90, 110, 22);
    realTime->setBounds (520, getHeight() - 50, 110, 22);
    songDial->setBounds (640, getHeight() - 90, 36, 36);
    realDial->setBounds (640, getHeight() - 50, 36, 36);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainPageJ::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == startStopButton)
    {
        //[UserButtonCode_startStopButton] -- add your button handler code here..
      peer_.startStopButtonClicked();
        //[/UserButtonCode_startStopButton]
    }
    else if (buttonThatWasClicked == loopingButton)
    {
      // peer_.loopingButtonClicked();

        //[/UserButtonCode_loopingButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainPageJ::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == zoomSlider)
    {
        //[UserSliderCode_zoomSlider] -- add your slider handling code here..
        //[/UserSliderCode_zoomSlider]
    }
    else if (sliderThatWasMoved == timeScaleSlider)
    {
        //[UserSliderCode_timeScaleSlider] -- add your slider handling code here..
        //[/UserSliderCode_timeScaleSlider]
    }
    else if (sliderThatWasMoved == pitchScaleSlider)
    {
        //[UserSliderCode_pitchScaleSlider] -- add your slider handling code here..
        //[/UserSliderCode_pitchScaleSlider]
    }

    //[UsersliderValueChanged_Post]
    peer_.sliderValueChanged(sliderThatWasMoved);
    //[/UsersliderValueChanged_Post]
}

void MainPageJ::sliderDragEnded (Slider* sliderThatWasMoved)
{
  peer_.sliderDragEnded(sliderThatWasMoved);
}
