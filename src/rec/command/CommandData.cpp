#include "rec/command/CommandData.h"

namespace rec {
namespace command {

namespace {

Def<Commands> COMMANDS(
"command { type: ADD_LOOP_POINT, category: \"Loops\"}"
"");

Def<Commands> DESCRIPTIONS;
Def<Commands> KEY_PRESSES;

}  // namespace


void merge(CommandTable* map, const Commands& commands, MergeType mergeType) {
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command::Type type = commands.command(i).type();
    CommandTable::iterator i = map->find(type);
    if (i == map->end()) {
      if (mergeType == NEW)
        map->insert(i, make_pair(type, commands.command(i)));
      else
        LOG(ERROR) << "No existing command " << type;
    } else {
      if (mergeType == MERGE)
        i->second->MergeFrom(type, commands.command(i));
      else
        LOG(ERROR) << "Can't replacing existing command " << type;
    }
  }
}

const Commands& commands() { return COMMANDS; }
const Commands& descriptions(const Access&) { return DESCRIPTIONS; }
const Commands& keyPresses(const Access&) { return KEY_PRESSES; }

}  // namespace command
}  // namespace rec
