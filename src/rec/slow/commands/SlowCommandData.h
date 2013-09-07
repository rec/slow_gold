#ifndef __REC_COMMAND_DATA_SLOWCOMMANDDATA__
#define __REC_COMMAND_DATA_SLOWCOMMANDDATA__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/program/Menu.pb.h"

namespace rec {

namespace command { class CommandData; }

namespace slow {

class Instance;

command::Commands makeCommand();
command::CommandData* createSlowCommandData(Instance*);
program::Menus createMenus();
command::KeyStrokeCommandMapProto makeKeyBindings();

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_DATA_SLOWCOMMANDDATA__
