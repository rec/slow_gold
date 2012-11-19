#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/CommandDatabase.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandTarget.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/command/TargetManager.h"
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
      midiCommandMap_(new command::MidiCommandMap(&commandManager_)) {
  target_.reset(new CommandTarget(this, &table_));
  commandData_.reset(slow::createSlowCommandData(i));
  commandManager_.setFirstCommandTarget(target_.get());
  targetManager_.reset(new command::TargetManager(&commandManager_, &table_));
  i->window_->addKeyListener(commandManager_.getKeyMappings());
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  midiCommandMap_->addCommands(data::getProto<command::CommandMapProto>());
  targetManager_->addListener(this);
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::addCommands() {
  command::fillCommandRecordTable(&table_, *commandData_);
  commandManager_.registerAllCommandsForTarget(target_.get());
  loadKeyboardBindings(table_, &commandManager_);
  window()->getAppleMenu()->addCommandItem(&commandManager_,
                                           Command::ABOUT_THIS_PROGRAM);
}

void Target::operator()(None) {
  if (window())
    thread::callAsync(window(), &app::Window::stopAboutWindow);
}

bool Target::perform(const InvocationInfo& info) {
  return targetManager_->perform(info);
}


}  // namespace slow
}  // namespace rec

