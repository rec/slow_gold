#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Position.h"
#include "rec/slow/callbacks/Callbacks.h"

using namespace rec::command;

namespace rec {
namespace slow {

Target::Target(Instance* i)
    : HasInstance(i),
      manager_(i->window_),
      midiCommandMap_(new command::MidiCommandMap(manager_.commandManager())) {
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  (*midiCommandMap_)(data::get<command::CommandMapProto>());
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::addCommands() {
  ptr<CallbackTable> callbacks(createCallbackTable(instance_));

  CommandTable cmds = command::getCommandTable();
  for (CommandTable::const_iterator i = cmds.begin(); i != cmds.end(); ++i) {
    const Command& c = *i->second;
    CommandID id = Position::toCommandID(c);
    CallbackTable::const_iterator j = callbacks->find(id);
    if (j == callbacks->end()) {
      if (c.type() != Command::RECENT_FILES || c.index() >= 0)
        LOG(ERROR) << "No callback for " << c.ShortDebugString();
    } else {
      const String& menu = c.desc().menu_size() ? 
          str(c.desc().menu(0)) : String();
      const String& desc = str(c.desc().full());
      const String& category = str(c.category());

      manager_.addCallback(id, j->second, menu, category, desc);
    }
  }

  targetManager()->registerAllCommandsForTarget();
}

}  // namespace slow
}  // namespace rec

