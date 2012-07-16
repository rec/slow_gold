#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/CommandDatabase.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/data/DataOps.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::command;

namespace rec {
namespace slow {

Target::Target(Instance* i)
    : HasInstance(i),
      manager_(slow::createSlowCommandData(i)),
      midiCommandMap_(new command::MidiCommandMap(manager_.commandManager())) {
  i->window_->addKeyListener(manager_.commandManager()->getKeyMappings());
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  (*midiCommandMap_)(data::getProto<command::CommandMapProto>());
  manager_.addListener(this);
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::addCommands() {
  manager_.addCommands();
  window()->getAppleMenu()->addCommandItem(manager_.commandManager(),
                                             Command::ABOUT_THIS_PROGRAM);
}

void Target::operator()(None) {
  if (window())
    thread::callAsync(window(), &app::Window::stopAboutWindow);
}

}  // namespace slow
}  // namespace rec

