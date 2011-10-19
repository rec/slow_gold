#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/MidiCommandMapEditor.h"
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

const char* LOWER[] = {" the first", " the previous", " the current",
                       " the next", " the last"};
const char* CAP[] = {" First", " Previous", " Current", " Next", " Last"};

void addCommand(TargetManager* manager, Callback* cb, const Command& c) {
  CommandID t = c.type();
  const String& menu = str(c.desc().menu());
  const String& desc = str(c.desc().full());
  const String& category = str(c.category());
  uint32 repeat = c.repeat_count();
  if (!repeat) {
    manager->addCallback(t, cb, menu, category, desc);
    return;
  }
  int b = t * Command::BANK_SIZE;
  for (int i = 0; i <= LAST - FIRST; ++i) {
    String m2 = String::formatted(menu, CAP[i]);
    String d2 = String::formatted(desc, LOWER[i]);
    manager->addCallback(b + i, cb, m2, category, d2);
  }

  for (int i = 0; i < repeat; ++i) {
    String n = " " + String(i + 1);
    const char* ns = n.toUTF8();
    String menu = String::formatted(menu, ns);
    String desc = String::formatted(desc, ns);
    manager->addCallback(b + i - FIRST, cb, menu, category, desc);
  }
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
#include "rec/util/thread/FunctionCallback.h"

using rec::thread::functionCallback;

#include "rec/audio/source/Player.h"
#include "rec/command/Command.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/LoopCommands.h"
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

  // Defined by Juce.
  add(Command::DEL, functionCallback(cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.");

  add(Command::CUT, functionCallback(cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.");

  add(Command::COPY, functionCallback(copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.");

  add(Command::PASTE, functionCallback(pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.");

  add(Command::SELECT_ALL,
      "Select All", "Selection",
      "Select all of the file");

  add(Command::DESELECT_ALL,
      "Select None", "Selection",
      "Select none of the file");


  //
  // REC commands!
  //
  add(Command::ADD_LOOP_POINT, functionCallback(&addLoopPoint, instance_),
      "Add Loop Point", "Loops",
      "Add a loop point at the current time.");

  add(Command::AUDIO_PREFERENCES, methodCallback(device()->setupPage_.get(),
                                                 &gui::audio::SetupPage::show,
                                                 &components()->mainPage_),
      "Audio Preferences...", "Audio",
      "Open the Audio Preferences pane.");

  add(Command::CLEAR_NAVIGATOR, functionCallback(&clearNavigator),
      "Clear Navigator", "File",
      "Clear all files and directories from "
      "the navigator pane.");

  add(Command::CLEAR_LOOPS,
      "Clear Loops", "Loops",
      "Delete all loop points");

  add(Command::CLOSE_FILE, methodCallback(model(), &Model::setFile, VirtualFile()),
      "Close", "File",
      "Close the current file");

  add(Command::DIM_VOLUME_TOGGLE,
      functionCallback(&dimVolumeToggle, instance_),
      "Toggle audio dim", "Audio",
      "Toggle audio dim on and off.");

  add(Command::EJECT_CDS, functionCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::INVERT_LOOP_SELECTION,
      "Invert Selection", "Selection",
      "Unselect everything selected and vice-versa.");

  add(Command::KEYBOARD_MAPPINGS,
      functionCallback(&keyboardMappings, instance_),
      "Edit Keyboard Mappings...", "File",
      "Edit keyboard mappings for commands.");

  add(Command::MIDI_MAPPINGS,
      functionCallback(&midiMappings, instance_),
      "Edit Midi Mappings...", "File",
      "Edit midi mappings for commands.");

  add(Command::MUTE_VOLUME_TOGGLE,
      functionCallback(&muteVolumeToggle, instance_),
      "Toggle audio mute", "Audio",
      "Toggle audio mute on and off.");

  add(Command::NUDGE_BEGIN_LEFT,
      functionCallback(&nudgeBeginLeft, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_BEGIN_RIGHT,
      functionCallback(&nudgeBeginRight, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_END_LEFT,
      functionCallback(&nudgeEndLeft, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_END_RIGHT,
      functionCallback(&nudgeEndRight, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_VOLUME_DOWN,
      functionCallback(&nudgeVolumeDown, instance_),
      "Nudge gain down", "Audio",
      "Nudge gain down by 2dB");

  add(Command::NUDGE_VOLUME_UP,
      functionCallback(&nudgeVolumeUp, instance_),
      "Nudge gain up", "Audio",
      "Nudge gain up by 2dB");

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.");

  add(Command::RESET_GAIN_TO_UNITY,
      functionCallback(resetGainToUnity, instance_),
      "Reset level", "Audio",
      "Reset audio level to 0 dB");

  add(Command::RECENT_FILES,
      functionCallback(recentFiles, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::REDO,
      functionCallback(&redo),
      "Redo", "Edit",
      "Redo a previously undone command.");

  add(Command::TOGGLE_WHOLE_SONG_LOOP,
      "Toggle Whole Segment Selection", "Selection",
      "Toggle selection between the current segment and the whole song.");

  add(Command::TOGGLE_START_STOP,
      methodCallback(player(), &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause");

  add(Command::TOGGLE_STRETCH_ENABLE,
      functionCallback(&toggleStretchEnable, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_CLOSE,
      functionCallback(&treeClose, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_DOWN,
      functionCallback(&treeDown, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_LEFT,
      functionCallback(&treeLeft, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_OPEN,
      functionCallback(&treeOpen, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_RIGHT,
      functionCallback(&treeRight, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_UP,
      functionCallback(&treeUp, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::UNDO,
      functionCallback(&undo),
      "Undo", "Edit",
      "Undoes a previous command.");

  add(Command::ZOOM_IN,
      functionCallback(&zoomIn, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::ZOOM_OUT,
      functionCallback(&zoomOut, instance_),
      "NAME", "(None)",
      "Documentation");

  targetManager()->registerAllCommandsForTarget();
}
#endif

}  // namespace slow
}  // namespace rec

