#include "rec/slow/TargetCommands.h"

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Gain.h"
#include "rec/command/Command.h"
#include "rec/command/KeyCommandMapEditor.h"
#include "rec/command/MidiCommandMapEditor.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/SetupPage.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Target.h"
#include "rec/util/Math.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

namespace {

void addLoopPoint(Instance* i) {
  i->components_->loops_.addLoopPoint(i->player_->getTime());
}

void nudgeVolumeDown(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->model_->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() - 1.0);
    data::set(gain, i->model_->file());
  }
}

void nudgeVolumeUp(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->model_->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() + 1.0);
    data::set(gain, i->model_->file());
  }
}

void clearNavigator(Instance *) { data::set(VirtualFileList()); }

void dimVolumeToggle(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->model_->file()));
  gain.set_dim(!gain.dim());
  data::set(gain, i->model_->file());
}

void muteVolumeToggle(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->model_->file()));
  gain.set_mute(!gain.mute());
  data::set(gain, i->model_->file());
}

void resetGainToUnity(Instance* i) {
  audio::Gain gain(data::get<audio::Gain>(i->model_->file()));
  gain.set_gain(0);
  data::set(gain, i->model_->file());
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

}  // namespace


using namespace rec::command;

void addInstanceCommands(CallbackTable* t, Instance* i) {
  using namespace rec::gui;
  using thread::functionCallback;
  using thread::methodCallback;
  using rec::gui::audio::SetupPage;
  using rec::audio::source::Player;

  (*t)[Command::ADD_LOOP_POINT] = functionCallback(addLoopPoint, i);
  (*t)[Command::CLEAR_NAVIGATOR] = functionCallback(clearNavigator, i);
  (*t)[Command::DIM_VOLUME_TOGGLE] = functionCallback(dimVolumeToggle, i);
  (*t)[Command::KEYBOARD_MAPPINGS] = functionCallback(keyboardMappings, i);
  (*t)[Command::MIDI_MAPPINGS] = functionCallback(midiMappings, i);
  (*t)[Command::MUTE_VOLUME_TOGGLE] = functionCallback(muteVolumeToggle, i);
  (*t)[Command::NUDGE_BEGIN_LEFT] = functionCallback(nudgeBeginLeft, i);
  (*t)[Command::NUDGE_BEGIN_RIGHT] = functionCallback(nudgeBeginRight, i);
  (*t)[Command::NUDGE_END_LEFT] = functionCallback(nudgeEndLeft, i);
  (*t)[Command::NUDGE_END_RIGHT] = functionCallback(nudgeEndRight, i);
  (*t)[Command::NUDGE_VOLUME_DOWN] = functionCallback(nudgeVolumeDown, i);
  (*t)[Command::NUDGE_VOLUME_UP] = functionCallback(nudgeVolumeUp, i);
  (*t)[Command::RECENT_FILES] = functionCallback(recentFiles, i);
  (*t)[Command::RESET_GAIN_TO_UNITY] = functionCallback(resetGainToUnity, i);
  (*t)[Command::TOGGLE_STRETCH_ENABLE] = functionCallback(toggleStretchEnable, i);
  (*t)[Command::TREE_CLOSE] = functionCallback(treeClose, i);
  (*t)[Command::TREE_DOWN] = functionCallback(treeDown, i);
  (*t)[Command::TREE_LEFT] = functionCallback(treeLeft, i);
  (*t)[Command::TREE_OPEN] = functionCallback(treeOpen, i);
  (*t)[Command::TREE_RIGHT] = functionCallback(treeRight, i);
  (*t)[Command::TREE_UP] = functionCallback(treeUp, i);
  (*t)[Command::ZOOM_IN] = functionCallback(zoomIn, i);
  (*t)[Command::ZOOM_OUT] = functionCallback(zoomOut, i);

  (*t)[Command::AUDIO_PREFERENCES] = methodCallback(
      i->device_->setupPage_.get(), &SetupPage::show,
      &i->components_->mainPage_);
  (*t)[Command::CLOSE_FILE] = methodCallback(i->model_.get(), &Model::setFile,
                                             VirtualFile());
  (*t)[Command::EJECT_CDS] = functionCallback(&cd::ejectAll);
  (*t)[Command::OPEN] = functionCallback(&dialog::openOneFile,
                                         i->listeners_.get());
  (*t)[Command::TOGGLE_START_STOP] = methodCallback(i->player_.get(),
                                                    &Player::toggle);
}


void addGlobalCommands(CallbackTable* t) {
}

}  // namespace slow
}  // namespace rec
