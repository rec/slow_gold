#include "rec/command/data/CommandData.h"
#include "rec/command/data/Commands.def.h"
#include "rec/command/data/Descriptions.def.h"
#include "rec/command/data/KeyPresses.def.h"

namespace rec {
namespace command {

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

const Commands& commands() { return *data::commands; }
const Commands& descriptions(const Access&) { return *data::descriptions; }
const Commands& keyPresses(const Access&) { return *data::keyPresses; }

// Internationalization goes here!

}  // namespace command
}  // namespace rec
