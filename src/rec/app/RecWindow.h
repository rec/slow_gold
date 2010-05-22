#ifndef __REC_WINDOW
#define __REC_WINDOW

#include "rec/base/scoped_ptr.h"
#include "juce_amalgamated.h"

namespace rec {

class RecWindow  : public DocumentWindow {
 public:
  RecWindow();
  ~RecWindow();

  void closeButtonPressed();

  juce_UseDebuggingNewOperator

 private:
  // the command manager object used to dispatch command events
  scoped_ptr<ApplicationCommandManager> commandManager;

  Component* taskbarIcon;
};

}  // namespace rec

#endif   // __REC_WINDOW
