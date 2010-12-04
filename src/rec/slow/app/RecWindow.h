#ifndef __REC_WINDOW
#define __REC_WINDOW

#include "rec/slow/Preferences.h"

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

#if 0
  Component* taskbarIcon;
#endif
};

}  // namespace rec

#endif   // __REC_WINDOW
