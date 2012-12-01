#ifndef __REC_COMMAND_COMMANDENTRYWINDOW__
#define __REC_COMMAND_COMMANDENTRYWINDOW__

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandMapEditor;

class CommandEntryWindow  : public juce::AlertWindow {
 public:
  CommandEntryWindow(const String& caption, CommandMapEditor* editor);
	CommandMapEditor* editor() { return editor_; }
  virtual const string lastKey() const = 0;

 private:
  CommandMapEditor* editor_;

  JUCE_DECLARE_NON_COPYABLE(CommandEntryWindow);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDENTRYWINDOW__
