#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/base/base.h"

namespace rec {
namespace command {

juce::ModifierKeys getDefaultMods() {
  return juce::ModifierKeys(juce::ModifierKeys::
#if JUCE_MAC
commandModifier
#else
ctrlModifier
#endif
                      );
}

ApplicationCommandInfo makeInfo(
    CommandID id, const String& name,
    const String& category, const String& desc,
    int flags = 0, int keyCode = 0,
    const ModifierKeys& mod = ModifierKeys(getDefaultMods()));

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
