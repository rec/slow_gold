#ifndef __REC_WINDOW
#define __REC_WINDOW

#include "rec/slow/Preferences.h"
#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;

namespace rec {

class RecWindow  : public juce::DocumentWindow {
 public:
  RecWindow();
  ~RecWindow();

  void closeButtonPressed();

  juce_UseDebuggingNewOperator

 private:
  // the command manager object used to dispatch command events
  ApplicationCommandManager commandManager;

  Component* taskbarIcon;
};

}  // namespace rec

#endif   // __REC_WINDOW
