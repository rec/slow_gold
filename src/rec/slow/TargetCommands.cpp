#include "rec/slow/TargetCommands.h"
#include "rec/audio/Audio.h"
#include "rec/audio/util/Gain.h"
#include "rec/command/KeyCommandMapEditor.h"
#include "rec/command/MidiCommandMapEditor.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Target.h"
#include "rec/audio/source/Player.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

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

void clearNavigator() { data::set(VirtualFileList()); }

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
    PlatformUtilities::beep();
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
    PlatformUtilities::beep();
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

}  // namespace slow
}  // namespace rec
