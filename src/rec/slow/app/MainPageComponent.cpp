/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  19 Mar 2010 9:28:39pm

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
#include "rec/slow/Preferences.h"

//[/Headers]

#include "MainPageComponent.h"
#include "MainPageJ.h"
#include "AudioSetupPage.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainPageComponent::MainPageComponent ()
    : tabbedComponent (0)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (30);
    tabbedComponent->addTab (T("File Playback"), Colours::lightgrey, new MainPageJ (deviceManager), true);
    tabbedComponent->addTab (T("Audio Device Setup"), Colours::lightgrey, new AudioSetupPage (deviceManager), true);
    tabbedComponent->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainPageComponent::~MainPageComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (tabbedComponent);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainPageComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainPageComponent::resized()
{
    tabbedComponent->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================
Component* createAudioDemo()
{
    return new MainPageComponent();
}

void MainPageComponent::loadRecentFile(int menuItemId) {
  MainPageJ* main = (MainPageJ*) tabbedComponent->getTabContentComponent(0);
  main->loadRecentFile(menuItemId);
}

void MainPageComponent::cut() {
  MainPageJ* main = (MainPageJ*) tabbedComponent->getTabContentComponent(0);
  main->cut();
}
void MainPageComponent::paste() {
  MainPageJ* main = (MainPageJ*) tabbedComponent->getTabContentComponent(0);
  main->paste();

}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainPageComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TABBEDCOMPONENT name="new tabbed component" id="83c980d7793cdced" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" orientation="top"
                   tabBarDepth="30" initialTab="0">
    <TAB name="File Playback" colour="ffd3d3d3" useJucerComp="1" contentClassName=""
         constructorParams="deviceManager" jucerComponentFile="MainPageJ.cpp"/>
    <TAB name="Audio Device Setup" colour="ffd3d3d3" useJucerComp="1"
         contentClassName="" constructorParams="deviceManager" jucerComponentFile="AudioSetupPage.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
