#include "rec/slow/Target.h"

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/MidiCommandMapEditor.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/LoopCommands.h"
#include "rec/slow/Model.h"
#include "rec/slow/Position.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/TargetCommands.h"
#include "rec/util/Math.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/thread/FunctionCallback.h"

using rec::thread::methodCallback;
using rec::thread::functionCallback;
using rec::command::Command;

namespace rec {
namespace slow {

namespace {

// TODO: move out of here.
void addLoopPoint(Instance* i) {
  i->components_->loops_.addLoopPoint(i->player_->getTime());
}

}

Target::Target(Instance* i)
    : HasInstance(i),
      targetManager_(i->window_),
      midiCommandMap_(new command::MidiCommandMap(targetManager_.commandManager())) {
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  (*midiCommandMap_)(data::get<command::CommandMapProto>());
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::add(CommandID c, const String& name,
                 const String& category, const String& desc) {
  add(c,
      functionCallback(&executeLoopCommand, instance_, static_cast<Command::Type>(c)),
      name, category, desc);
}

namespace {

const char* LOWER[] = {" the first", " the previous", " the current",
                       " the next", " the last"};
const char* CAP[] = {" First", " Previous", " Current", " Next", " Last"};

}  // namespace

void Target::addBank(Command::Type command, const String& menu,
                     const String& desc, const String& cat) {
  CommandID c = command;
  for (int i = 0; i <= LAST - FIRST; ++i, ++c) {
    add(c, String::formatted(menu, CAP[i], ""), cat,
        String::formatted(desc, LOWER[i], ""));
  }

  for (int i = 0; i < SLOT_COUNT; ++i, ++c) {
    String n = " " + String(i + 1);
    const char* ns = n.toUTF8();
    add(c, String::formatted(menu, "", ns), cat,
    	  String::formatted(desc, "", ns));
  }
}

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

}  // namespace slow
}  // namespace rec

