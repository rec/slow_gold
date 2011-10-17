#include "rec/command/CommandData.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace command {

namespace {

Def<Commands> COMMANDS(
"command { type: ADD_LOOP_POINT, category: \"Loops\"}"
"");

Def<Commands> DESCRIPTIONS("");
Def<Commands> KEY_PRESSES("");

}  // namespace


void merge(CommandTable* map, const Commands& commands, MergeType mergeType) {
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& cmd = commands.command(i);
    const Command::Type type = cmd.type();
    CommandTable::iterator j = map->find(type);
    if (j == map->end()) {
      if (mergeType == NEW)
        map->insert(j, std::make_pair(type, new Command(cmd)));
      else
        LOG(ERROR) << "No existing command " << type;
    } else {
      if (mergeType == MERGE)
        j->second->MergeFrom(cmd);
      else
        LOG(ERROR) << "Can't replacing existing command " << type;
    }
  }
}

const Commands& commands() { return *COMMANDS; }
const Commands& descriptions(const Access&) { return *DESCRIPTIONS; }
const Commands& keyPresses(const Access&) { return *KEY_PRESSES; }

}  // namespace command
}  // namespace rec
