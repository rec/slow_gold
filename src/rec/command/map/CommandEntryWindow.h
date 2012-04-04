#ifndef __REC_COMMAND_COMMANDENTRYWINDOW__
#define __REC_COMMAND_COMMANDENTRYWINDOW__

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandEntryWindow  : public juce::AlertWindow {
 public:
  CommandEntryWindow(const String& caption);

  static void translateAll();

 private:
  JUCE_DECLARE_NON_COPYABLE (CommandEntryWindow);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDENTRYWINDOW__
