#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/slow/Menus.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/callbacks/Callbacks.h"

using namespace rec::command;

namespace rec {
namespace slow {

Target::Target(Instance* i)
    : HasInstance(i),
      midiCommandMap_(new command::MidiCommandMap(manager_.commandManager())) {
  i->window_->addKeyListener(manager_.commandManager()->getKeyMappings());
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  (*midiCommandMap_)(data::get<command::CommandMapProto>());
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::addCommands() {
  CommandRecordTable* table = manager_.commandRecordTable();
  addCommandDatabase(table, menus());
  addCallbacks(instance_, table);
  manager_.addCallbacks();
  targetManager()->registerAllCommandsForTarget();
}

}  // namespace slow
}  // namespace rec

