#include "rec/command/Command.h"

namespace rec {
namespace command {

ApplicationCommandInfo makeInfo(CommandID id, const String& name,
                                const String& category, const String& desc,
                                int flags, int key, const ModifierKeys& mod) {

  ApplicationCommandInfo i(id);
  i.setInfo(name, desc, category, flags);
  if (key)
    i.addDefaultKeypress(key, mod);

  return i;
}

}  // namespace command
}  // namespace rec
