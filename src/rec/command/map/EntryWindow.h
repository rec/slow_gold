#ifndef __REC_COMMAND_COMMANDENTRYWINDOW__
#define __REC_COMMAND_COMMANDENTRYWINDOW__

#include "rec/base/base.h"

namespace rec {
namespace command {

class Editor;

class EntryWindow  : public juce::AlertWindow {
 public:
  EntryWindow(const String& caption, Editor* editor);
	Editor* editor() { return editor_; }

 private:
  Editor* editor_;

  JUCE_DECLARE_NON_COPYABLE(EntryWindow);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDENTRYWINDOW__
