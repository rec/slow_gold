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

#ifndef __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
#define __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__

//[Headers]     -- You can add your own extra header files here --
#include "JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    This component creates the set of tabs that hold the various
    audio demo pages..
                                                                    //[/Comments]
*/
class MainPageComponent  : public Component
{
public:
    //==============================================================================
    MainPageComponent ();
    ~MainPageComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void loadRecentFile(int menuItemId);
    void cut();
    void paste();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioDeviceManager deviceManager;
    //[/UserVariables]

    //==============================================================================
    TabbedComponent* tabbedComponent;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainPageComponent (const MainPageComponent&);
    const MainPageComponent& operator= (const MainPageComponent&);
};


#endif   // __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
