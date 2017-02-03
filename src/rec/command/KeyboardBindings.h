#pragma once

#include "rec/base/base.h"

#include "rec/command/map/CommandMap.pb.h"

namespace rec {
namespace command {

class CommandMapProto;

void loadKeyboardBindings(ApplicationCommandManager*);
void saveKeyboardBindings(const CommandMapProto&);

CommandMapProto getKeyboardBindings();

}  // namespace command
}  // namespace rec

