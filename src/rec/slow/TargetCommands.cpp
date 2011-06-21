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
#include "rec/slow/Selections.h"
#include "rec/slow/Target.h"
#include "rec/audio/source/Player.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

void clearNavigator() { persist::set(VirtualFileList()); }


void dimVolumeToggle(Instance* i) {
  audio::Gain gain(persist::get<audio::Gain>(i->model_->file()));
  gain.set_dim(!gain.dim());
  persist::set(gain, i->model_->file());
}

void muteVolumeToggle(Instance* i) {
  audio::Gain gain(persist::get<audio::Gain>(i->model_->file()));
  gain.set_mute(!gain.mute());
  persist::set(gain, i->model_->file());
}

void nudgeVolumeDown(Instance* i) {
  audio::Gain gain(persist::get<audio::Gain>(i->model_->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() - 1.0);
    persist::set(gain, i->model_->file());
  }
}

void nudgeVolumeUp(Instance* i) {
  audio::Gain gain(persist::get<audio::Gain>(i->model_->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() + 1.0);
    persist::set(gain, i->model_->file());
  }
}

void resetGainToUnity(Instance* i) {
  audio::Gain gain(persist::get<audio::Gain>(i->model_->file()));
  gain.set_level(0);
  persist::set(gain, i->model_->file());
}


void jumpToLoopPoint(Instance* i, int offset) {
  LoopPointList loops(i->model_->loopPointList());
  SamplePosition time = i->player_->getNextReadPosition();
  int j = 0, size = loops.loop_point_size();
  for (; j < size && time >= loops.loop_point(j).time(); ++j);
  j += offset;
  if (j >= size)
    j = 0;
  else if (j < 0)
    j = size - 1;

  SamplePosition pos = audio::timeToSamples(loops.loop_point(j).time());
  i->model_->jumpToSamplePosition(pos);
}

void jumpToStart(Instance* i) {
 i->model_->jumpToSamplePosition(i->model_->timeSelection().begin()->first);
}

void keyboardMappings(Instance* i) {
  gui::DialogLocker l;
  if (!l.isLocked()) {
    PlatformUtilities::beep();
    return;
  }

  ApplicationCommandManager* manager = i->target_->commandManager();
  command::KeyCommandMapEditor comp(*manager, *manager->getKeyMappings());
  comp.initialize(true);
  comp.setBounds(0, 0, 500, 1000);

  l.setModalComponent(&comp);
  juce::DialogWindow::showModalDialog("Select keyboard mappings",
                                      &comp, NULL, juce::Colours::white,
                                      true, true, true);
  i->target_->saveKeyboardBindings();
}

void midiMappings(Instance* i) {
  gui::DialogLocker l;
  if (!l.isLocked()) {
    PlatformUtilities::beep();
    return;
  }

  ApplicationCommandManager* manager = i->target_->commandManager();
  command::MidiCommandMapEditor comp(*manager, *i->target_->midiCommandMap());
  comp.initialize(true);
  comp.setBounds(0, 0, 500, 1000);

  l.setModalComponent(&comp);
  juce::DialogWindow::showModalDialog("Select MIDI mappings",
                                      &comp, NULL, juce::Colours::white,
                                      true, true, true);
  DLOG(INFO) << "Here 2!";
  persist::set(i->target_->midiCommandMap()->getProto());
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

void toggleWholeSongLoop(Instance* i) {
}

void toggleStartStop(Instance* i) {
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
