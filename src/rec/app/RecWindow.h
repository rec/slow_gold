#ifndef __REC_WINDOW
#define __REC_WINDOW

#include "rec/slow/Preferences.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {

class RecWindow  : public DocumentWindow {
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
