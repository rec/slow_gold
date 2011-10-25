#include "rec/slow/callbacks/InstanceCallbacks.h"

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Gain.h"
#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/data/Data.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/SetupPage.h"
#include "rec/slow/Components.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/Model.h"
#include "rec/slow/Target.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

namespace {

void addLoopPoint(Instance* i) {
  i->components_->loops_.addLoopPoint(i->player_->getTime());
}

void nudgeVolumeDown(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() - 1.0);
    data::set(gain, i->file());
  }
}

void nudgeVolumeUp(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() + 1.0);
    data::set(gain, i->file());
  }
}

void clearLoops(Instance *i) {
  LoopPointList loops;
  loops.add_loop_point();
  data::set(loops, i->file());
}

void clearNavigator(Instance *) { data::set(VirtualFileList()); }

void dimVolumeToggle(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->file()));
  gain.set_dim(!gain.dim());
  data::set(gain, i->file());
}

void muteVolumeToggle(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->file()));
  gain.set_mute(!gain.mute());
  data::set(gain, i->file());
}

void resetGainToUnity(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->file()));
  gain.set_gain(0);
  data::set(gain, i->file());
}

void keyboardMappings(Instance* i) {
  gui::DialogLocker l;
  if (!l.isLocked()) {
    beep();
    return;
  }

  ApplicationCommandManager* manager = i->target_->targetManager()->commandManager();
  command::KeyCommandMapEditor comp(*manager, *manager->getKeyMappings());
  comp.initialize(true);
  comp.setBounds(0, 0, 500, 1000);

  l.setModalComponent(&comp);
  juce::DialogWindow::showModalDialog("Select keyboard mappings",
                                      &comp, NULL, juce::Colours::white,
                                      true, true, true);
  i->target_->targetManager()->saveKeyboardBindings();
}

void midiMappings(Instance* i) {
  gui::DialogLocker l;
  if (!l.isLocked()) {
    beep();
    return;
  }

  ApplicationCommandManager* manager = i->target_->targetManager()->commandManager();
  command::MidiCommandMapEditor comp(*manager, *i->target_->midiCommandMap());
  comp.initialize(true);
  comp.setBounds(0, 0, 500, 1000);

  l.setModalComponent(&comp);
  juce::DialogWindow::showModalDialog("Select MIDI mappings",
                                      &comp, NULL, juce::Colours::white,
                                      true, true, true);
  data::set(i->target_->midiCommandMap()->getProto());
}


void nudgeBeginLeft(Instance* i) {
}

void nudgeBeginRight(Instance* i) {
}

void nudgeEndLeft(Instance* i) {
}

void nudgeEndRight(Instance* i) {
}

void recentFiles(Instance* i) {
}

void toggleStretchEnable(Instance* i) {
}

void treeClose(Instance* i) {
}

void treeDown(Instance* i) {
}

void treeLeft(Instance* i) {
}

void treeOpen(Instance* i) {
}

void treeRight(Instance* i) {
}

void treeUp(Instance* i) {
}

void zoomIn(Instance* i) {
}

void zoomOut(Instance* i) {
}

void audioPreferences(Instance* i) {
  i->device_->setupPage_->show(&i->components_->mainPage_);
}

void closeFile(Instance* i) {
  i->model_->setFile(VirtualFile());
}

void open(Instance* i) {
  gui::dialog::openOneFile(i->model_.get());
}

void toggleStartStop(Instance* i) {
  i->player_->toggle();
}

}  // namespace

using namespace rec::command;

void addInstanceCallbacks(CallbackTable* c, Instance* i) {
  using namespace rec::gui;
  using rec::gui::audio::SetupPage;
  using rec::audio::source::Player;

  add(c, Command::ADD_LOOP_POINT, addLoopPoint, i);
  add(c, Command::AUDIO_PREFERENCES, audioPreferences, i);
  add(c, Command::CLEAR_LOOPS, clearLoops, i);
  add(c, Command::CLEAR_NAVIGATOR, clearNavigator, i);
  add(c, Command::CLOSE_FILE, closeFile, i);
  add(c, Command::DIM_VOLUME_TOGGLE, dimVolumeToggle, i);
  add(c, Command::KEYBOARD_MAPPINGS, keyboardMappings, i);
  add(c, Command::MIDI_MAPPINGS, midiMappings, i);
  add(c, Command::MUTE_VOLUME_TOGGLE, muteVolumeToggle, i);
  add(c, Command::NUDGE_BEGIN_LEFT, nudgeBeginLeft, i);
  add(c, Command::NUDGE_BEGIN_RIGHT, nudgeBeginRight, i);
  add(c, Command::NUDGE_END_LEFT, nudgeEndLeft, i);
  add(c, Command::NUDGE_END_RIGHT, nudgeEndRight, i);
  add(c, Command::NUDGE_VOLUME_DOWN, nudgeVolumeDown, i);
  add(c, Command::NUDGE_VOLUME_UP, nudgeVolumeUp, i);
  add(c, Command::OPEN, open, i);
  add(c, Command::RECENT_FILES, recentFiles, i);
  add(c, Command::RESET_GAIN_TO_UNITY, resetGainToUnity, i);
  add(c, Command::TOGGLE_START_STOP, toggleStartStop, i);
  add(c, Command::TOGGLE_STRETCH_ENABLE, toggleStretchEnable, i);
  add(c, Command::TREE_CLOSE, treeClose, i);
  add(c, Command::TREE_DOWN, treeDown, i);
  add(c, Command::TREE_LEFT, treeLeft, i);
  add(c, Command::TREE_OPEN, treeOpen, i);
  add(c, Command::TREE_RIGHT, treeRight, i);
  add(c, Command::TREE_UP, treeUp, i);
  add(c, Command::ZOOM_IN, zoomIn, i);
  add(c, Command::ZOOM_OUT, zoomOut, i);
}

}  // namespace slow
}  // namespace rec
