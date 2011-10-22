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

namespace {

void addCommand(TargetManager* manager, Callback* cb, const Command& c) {
  CommandID t = c.type();
  const String& menu = str(c.desc().menu());
  const String& desc = str(c.desc().full());
  const String& category = str(c.category());
  manager->addCallback(t, cb, menu, category, desc);
}

}  // namespace


void Target::addCommands() {
  ptr<CallbackTable> callbacks(createCallbackTable(instance_));
  CommandTable cmds = command::getCommands();
  for (CommandTable::const_iterator i = cmds.begin(); i != cmds.end(); ++i) {
    const Command& c = *i->second;
    CallbackTable::const_iterator j = callbacks->find(c.type());
    if (j != callbacks->end())
      addCommand(&manager_, j->second, c);
    else
      LOG(ERROR) << "No callback for " << c.ShortDebugString();
  }

}

}  // namespace slow
}  // namespace rec

