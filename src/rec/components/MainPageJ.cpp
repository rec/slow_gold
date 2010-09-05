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

//[Headers] You can add your own extra header files here...
#include "MainPageK.h"
//[/Headers]

#include "MainPageJ.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainPageJ::MainPageJ(AudioDeviceManager& deviceManager)
    : zoomLabel (0),
      thumbnail (0),
      startStopButton (0),
      fileTreeComp (0),
      explanation (0),
      zoomSlider (0),
      timeScaleSlider (0),
      loopingButton (0),
      peer_(&deviceManager)
{
    addAndMakeVisible (zoomLabel = new Label (String::empty,
                                              T("zoom:")));
    zoomLabel->setFont (Font (15.0000f, Font::plain));
    zoomLabel->setJustificationType (Justification::centredRight);
    zoomLabel->setEditable (false, false, false);
    zoomLabel->setColour (TextEditor::textColourId, Colours::black);
    zoomLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (thumbnail = new rec::gui::AudioThumbnailComponent(&peer_));

    addAndMakeVisible (startStopButton = new TextButton (String::empty));
    startStopButton->setButtonText (T("Play/Stop"));
    startStopButton->addButtonListener (this);
    startStopButton->setColour (TextButton::buttonColourId, Colour (0xff79ed7f));

    addAndMakeVisible (fileTreeComp = new FileTreeComponent(*peer_.directoryList()));

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
    timeScaleSlider->setRange (0.1, 10, 0);
    timeScaleSlider->setSliderStyle (Slider::LinearHorizontal);
    timeScaleSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    timeScaleSlider->addListener (this);

    addAndMakeVisible (pitchScaleSlider = new Slider (T("Pitch Scale")));
    pitchScaleSlider->setTooltip (T("Drag this to set the pitchscale."));
    pitchScaleSlider->setRange (0.5, 2, 0);
    pitchScaleSlider->setSliderStyle (Slider::LinearHorizontal);
    pitchScaleSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    pitchScaleSlider->addListener (this);

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
    deleteAndZero (thumbnail);
    deleteAndZero (startStopButton);
    deleteAndZero (fileTreeComp);
    deleteAndZero (explanation);
    deleteAndZero (zoomSlider);
    deleteAndZero (loopingButton);
    deleteAndZero (timeScaleSlider);
    deleteAndZero (pitchScaleSlider);

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
    thumbnail->setBounds (16, getHeight() - 221, getWidth() - 32, 123);
    startStopButton->setBounds (16, getHeight() - 46, 150, 32);
    fileTreeComp->setBounds (16, 8, getWidth() - 32, getHeight() - 245);
    explanation->setBounds (224, getHeight() - 72, getWidth() - 248, 32);
    zoomSlider->setBounds (72, getHeight() - 90, 200, 24);
    loopingButton->setBounds (192, getHeight() - 40, 150, 24);
    timeScaleSlider->setBounds (300, getHeight() - 90, 200, 24);
    pitchScaleSlider->setBounds (300, getHeight() - 130, 200, 24);
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
      peer_.loopingButtonClicked();

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
    //[/UsersliderValueChanged_Post]
}

void MainPageJ::selectionChanged()
{
  peer_.selectionChanged();
}

//[MiscUserCode]
//[/MiscUserCode]



//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainPageJ" componentName=""
                 parentClasses="public Component, public FileBrowserListener"
                 variableInitialisers="peer_(&deviceManager),"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffd3d3d3"/>
  <LABEL name="" id="d4f78f975d81c8d3" memberName="zoomLabel" virtualName=""
         explicitFocusOrder="0" pos="16 90R 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="zoom:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <GENERICCOMPONENT name="" id="beef657b0e007936" memberName="thumbnail" virtualName=""
                    explicitFocusOrder="0" pos="16 221R 32M 123" class="rec::AudioThumbnailComponent"
                    params="&peer_"/>
  <TEXTBUTTON name="" id="abe446e2f3f09420" memberName="startStopButton" virtualName=""
              explicitFocusOrder="0" pos="16 46R 150 32" bgColOff="ff79ed7f"
              buttonText="Play/Stop" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="1de1dc6a18a9032b" memberName="fileTreeComp" virtualName=""
                    explicitFocusOrder="0" pos="16 8 32M 245M" class="FileTreeComponent"
                    params="peer_->directoryList"/>
  <LABEL name="" id="7db7d0a64ef21311" memberName="explanation" virtualName=""
         explicitFocusOrder="0" pos="224 72R 248M 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Select an audio file in the treeview above."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="14" bold="0" italic="0" justification="18"/>
  <SLIDER name="" id="38bbc108f4c96092" memberName="zoomSlider" virtualName=""
          explicitFocusOrder="0" pos="72 90R 200 24" min="0" max="1" int="0"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="2"/>
  <TOGGLEBUTTON name="looping button" id="df3101bc58894e22" memberName="loopingButton"
                virtualName="" explicitFocusOrder="0" pos="192 40R 150 24" buttonText="Loop sample?"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <SLIDER name="Time Scale" id="e5ac8e6febb7de41" memberName="timeScaleSlider"
          virtualName="" explicitFocusOrder="0" pos="120 856 150 24" tooltip="Drag this to set the timescale."
          min="0.1" max="10" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
