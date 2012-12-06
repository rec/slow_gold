#ifndef __REC_SLOW_COMMANDS_KEYSTROKEMAP__
#define __REC_SLOW_COMMANDS_KEYSTROKEMAP__

// Created by the command line:
// new --include=command/map/CommandMap.pb --proto=command::KeyStrokeCommandMapProto src/rec/slow/commands/KeyStrokeMap.def

#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/proto/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::KeyStrokeCommandMapProto> keyStrokeMap;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_KEYSTROKEMAP__
