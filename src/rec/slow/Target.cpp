#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Position.h"

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

void Target::addCommands(const CommandTable& cmds,
                         const CallbackTable& callbacks) {
  for (CommandTable::const_iterator i = cmds.begin(); i != cmds.end(); ++i) {
    const Command& c = *i->second;
    CallbackTable::const_iterator j = callbacks.find(c.type());
    if (j != callbacks.end())
      addCommand(&manager_, j->second, c);
    else
      LOG(ERROR) << "Couldn't add " << c.DebugString();
  }
}

#if 0

using rec::thread::functionCallback;

#include "rec/audio/source/Player.h"
#include "rec/command/Command.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/TargetCommands.h"
#include "rec/util/Math.h"
#include "rec/util/Undo.h"
#include "rec/util/cd/Eject.h"
using rec::thread::methodCallback;

//functionCallback(&executeLoopCommand, instance_, c),


void Target::addBankCommands() {
  addBank(Command::JUMP_SELECTED, "Jump To%s Selected Segment%s",
          "Jump to the start of%s selected segment%s", "Transport");

  addBank(Command::JUMP, "Jump To%s Segment%s",
          "Jump to the start of%s segment%s", "Transport");

  addBank(Command::SELECT_ONLY, "Select%s Segment%s Only",
          "Select%s segment%s only", "Transport");

  addBank(Command::SELECT, "Select%s Segment%s",
          "Select%s segment%s", "Transport");

  addBank(Command::TOGGLE, "Toggle%s Segment%s Selection",
          "Toggle%s segment%s between selected and unselected", "Transport");

  addBank(Command::UNSELECT, "Unselect%s Segment%s",
          "Unselect%s segment%s", "Transport");
}

void Target::addCommands() {
  using gui::audio::Loops;
  using rec::command::Command;

	addBankCommands();

  add(Command::SELECT_ALL,
      "Select All", "Selection",
      "Select all of the file");

  add(Command::DESELECT_ALL,
      "Select None", "Selection",
      "Select none of the file");

  add(Command::CLEAR_LOOPS,
      "Clear Loops", "Loops",
      "Delete all loop points");

  add(Command::INVERT_LOOP_SELECTION,
      "Invert Selection", "Selection",
      "Unselect everything selected and vice-versa.");

  add(Command::TOGGLE_WHOLE_SONG_LOOP,
      "Toggle Whole Segment Selection", "Selection",
      "Toggle selection between the current segment and the whole song.");


  targetManager()->registerAllCommandsForTarget();
}
#endif

}  // namespace slow
}  // namespace rec

