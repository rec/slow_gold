#ifndef __REC_PROGRAM_TYPES__
#define __REC_PROGRAM_TYPES__

#include <unordered_map>

#include "rec/data/UntypedDataListener.h"
#include "rec/program/Menu.pb.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace program {

typedef std::unordered_map<CommandID, command::Command> ProgramMap;
typedef std::unordered_map<string, Menu> MenuMap;
typedef std::unordered_map<string, MenuBar> MenuBarMap;
typedef vector<unique_ptr<UntypedDataListener>> DataListeners;

typedef std::unordered_map<CommandID, unique_ptr<Callback>> CallbackMap;

}  // namespace program
}  // namespace rec

#endif  // __REC_PROGRAM_TYPES__