#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace command {

inline ModifierKeys getDefaultMods() {
#if JUCE_MAC
  return ModifierKeys(juce::ModifierKeys::commandModifier);
#else
  return ModifierKeys(juce::ModifierKeys::ctrlModifier);
#endif
}

ApplicationCommandInfo makeInfo(
    CommandID id, const String& name,
    const String& category, const String& desc,
    int flags = 0, int keyCode = 0,
    const ModifierKeys& mod = ModifierKeys());

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
