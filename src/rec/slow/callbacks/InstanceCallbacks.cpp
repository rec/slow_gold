#include "rec/slow/callbacks/InstanceCallbacks.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Gain.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/data/Data.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/SetupPage.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Math.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::widget::waveform;

namespace {

static const int SELECTION_WIDTH_PORTION = 20;

void addLoopPoint(Instance* i) {
  audio::addLoopPointToEditable(i->file(), i->player_->getTime());
}

void addLoopPointClick(Instance* i) {
  // TODO
}

void nudgeVolumeDownOp(audio::Gain* gain) {
  if (!(gain->dim() || gain->mute()))
    gain->set_gain(gain->gain() - 1.0);
}

void nudgeVolumeDown(Instance* i) {
  data::apply(i->file(), nudgeVolumeDownOp);
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
  command::saveKeyboardBindings(manager);
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

void zoomOut(Instance* i) {
  widget::waveform::zoom(i->file(), i->length(), -1.0);
}

void zoomToSelection(Instance* i) {
  block::Block range = block::toBlock(i->currentTime_->timeSelection());
  int64 pad = block::getSize(range) / SELECTION_WIDTH_PORTION;

  ZoomProto zoom;
  zoom.set_begin(std::max(0LL, range.first - pad));
  zoom.set_end(std::min(i->length().get(), range.second + pad));
  data::set(zoom, i->file());
}

void audioPreferences(Instance* i) {
  i->device_->setupPage_->show(i->components_->mainPage_->panel());
}

void closeFile(Instance* i) {
  data::set(VirtualFile());
}

void open(Instance* i) {
  gui::dialog::openOneFile(i->currentFile_.get());
}

void quit(Instance* i) {
  i->window_->application()->systemRequestedQuit();
}

void toggleStartStop(Instance* i) {
  i->player_->toggle();
}

}  // namespace

using namespace rec::command;

void addInstanceCallbacks(CommandRecordTable* c, Instance* i) {
  using namespace rec::gui;
  using rec::gui::audio::SetupPage;
  using rec::audio::source::Player;

  addCallback(c, Command::ADD_LOOP_POINT, addLoopPoint, i);
  addCallback(c, Command::ADD_LOOP_POINT_CLICK, addLoopPoint, i);
  addCallback(c, Command::AUDIO_PREFERENCES, audioPreferences, i);
  addCallback(c, Command::CLEAR_LOOPS, clearLoops, i);
  addCallback(c, Command::CLEAR_NAVIGATOR, clearNavigator, i);
  addCallback(c, Command::CLOSE_FILE, closeFile, i);
  addCallback(c, Command::DIM_VOLUME_TOGGLE, dimVolumeToggle, i);
  addCallback(c, Command::KEYBOARD_MAPPINGS, keyboardMappings, i);
  addCallback(c, Command::MIDI_MAPPINGS, midiMappings, i);
  addCallback(c, Command::MUTE_VOLUME_TOGGLE, muteVolumeToggle, i);
  addCallback(c, Command::NUDGE_VOLUME_DOWN, nudgeVolumeDown, i);
  addCallback(c, Command::NUDGE_VOLUME_UP, nudgeVolumeUp, i);
  addCallback(c, Command::OPEN, open, i);
  addCallback(c, Command::QUIT, quit, i);
  addCallback(c, Command::RESET_GAIN_TO_UNITY, resetGainToUnity, i);
  addCallback(c, Command::TOGGLE_START_STOP, toggleStartStop, i);
  addCallback(c, Command::ZOOM_OUT, zoomOut, i);
  addCallback(c, Command::ZOOM_TO_SELECTION, zoomToSelection, i);
}

}  // namespace slow
}  // namespace rec
