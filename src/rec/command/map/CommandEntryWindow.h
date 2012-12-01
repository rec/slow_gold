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
  const string lastKey() const { return lastKey_; }
  virtual void listen(bool on) {}
  bool lastKeyEntered() const { return lastKeyEntered_; }

 protected:
  void setLastKey(const string&);

  bool lastKeyEntered_;
  string lastKey_;

 private:
  CommandMapEditor* editor_;


  JUCE_DECLARE_NON_COPYABLE(CommandEntryWindow);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDENTRYWINDOW__
