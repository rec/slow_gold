#ifndef __REC_PROGRAM_TYPES__
#define __REC_PROGRAM_TYPES__

#include <unordered_map>

#include "rec/program/Menu.pb.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace program {

typedef std::unordered_map<CommandID, command::Command> CommandMap;
typedef std::unordered_map<string, Menu> MenuMap;
typedef std::unordered_map<string, MenuBar> MenuBarMap;

typedef std::unordered_map<CommandID, unique_ptr<Callback>> CallbackMap;

}  // namespace program
}  // namespace rec

#endif  // __REC_PROGRAM_TYPES__
