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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AudioDemoPlaybackPage(2).h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudioDemoPlaybackPage::AudioDemoPlaybackPage (AudioDeviceManager& deviceManager_)
    : deviceManager (deviceManager_),
      thread ("audio file preview"),
      directoryList (0, thread),
      zoomLabel (0),
      thumbnail (0),
      startStopButton (0),
      fileTreeComp (0),
      zoomSlider (0),
      timeScaleSlider (0)
{
    addAndMakeVisible (zoomLabel = new Label (String::empty,
                                              T("zoom:")));
    zoomLabel->setFont (Font (15.0000f, Font::plain));
    zoomLabel->setJustificationType (Justification::centredRight);
    zoomLabel->setEditable (false, false, false);
    zoomLabel->setColour (TextEditor::textColourId, Colours::black);
    zoomLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (thumbnail = new DemoThumbnailComp());

    addAndMakeVisible (startStopButton = new TextButton (String::empty));
    startStopButton->setButtonText (T("Play/Stop"));
    startStopButton->addButtonListener (this);
    startStopButton->setColour (TextButton::buttonColourId, Colour (0xff79ed7f));

    addAndMakeVisible (fileTreeComp = new FileTreeComponent (directoryList));

    addAndMakeVisible (zoomSlider = new Slider (String::empty));
    zoomSlider->setRange (0, 1, 0);
    zoomSlider->setSliderStyle (Slider::LinearHorizontal);
    zoomSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    zoomSlider->addListener (this);
    zoomSlider->setSkewFactor (2);

    addAndMakeVisible (timeScaleSlider = new Slider (T("Time Scale")));
    timeScaleSlider->setTooltip (T("Drag this to set the timescale."));
    timeScaleSlider->setRange (0.1, 10, 0);
    timeScaleSlider->setSliderStyle (Slider::LinearHorizontal);
    timeScaleSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    timeScaleSlider->addListener (this);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AudioDemoPlaybackPage::~AudioDemoPlaybackPage()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (zoomLabel);
    deleteAndZero (thumbnail);
    deleteAndZero (startStopButton);
    deleteAndZero (fileTreeComp);
    deleteAndZero (zoomSlider);
    deleteAndZero (timeScaleSlider);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AudioDemoPlaybackPage::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AudioDemoPlaybackPage::resized()
{
    zoomLabel->setBounds (16, getHeight() - 90, 55, 24);
    thumbnail->setBounds (16, getHeight() - 221, getWidth() - 32, 123);
    startStopButton->setBounds (16, getHeight() - 46, 80, 30);
    fileTreeComp->setBounds (16, 8, getWidth() - 32, getHeight() - 245);
    zoomSlider->setBounds (72, getHeight() - 90, 200, 24);
    timeScaleSlider->setBounds (120, 856, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AudioDemoPlaybackPage::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == startStopButton)
    {
        //[UserButtonCode_startStopButton] -- add your button handler code here..
        //[/UserButtonCode_startStopButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AudioDemoPlaybackPage::sliderValueChanged (Slider* sliderThatWasMoved)
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioDemoPlaybackPage" componentName=""
                 parentClasses="public Component, public FileBrowserListener"
                 constructorParams="AudioDeviceManager&amp; deviceManager_" variableInitialisers="deviceManager (deviceManager_),&#10;thread (&quot;audio file preview&quot;),&#10;directoryList (0, thread)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffd3d3d3"/>
  <LABEL name="" id="d4f78f975d81c8d3" memberName="zoomLabel" virtualName=""
         explicitFocusOrder="0" pos="16 90R 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="zoom:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <GENERICCOMPONENT name="" id="beef657b0e007936" memberName="thumbnail" virtualName=""
                    explicitFocusOrder="0" pos="16 221R 32M 123" class="DemoThumbnailComp"
                    params=""/>
  <TEXTBUTTON name="" id="abe446e2f3f09420" memberName="startStopButton" virtualName=""
              explicitFocusOrder="0" pos="16 46R 80 30" bgColOff="ff79ed7f"
              buttonText="Play/Stop" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="1de1dc6a18a9032b" memberName="fileTreeComp" virtualName=""
                    explicitFocusOrder="0" pos="16 8 32M 245M" class="FileTreeComponent"
                    params="directoryList"/>
  <SLIDER name="" id="38bbc108f4c96092" memberName="zoomSlider" virtualName=""
          explicitFocusOrder="0" pos="72 90R 200 24" min="0" max="1" int="0"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="2"/>
  <SLIDER name="Time Scale" id="e5ac8e6febb7de41" memberName="timeScaleSlider"
          virtualName="" explicitFocusOrder="0" pos="120 856 150 24" tooltip="Drag this to set the timescale."
          min="0.1" max="10" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
