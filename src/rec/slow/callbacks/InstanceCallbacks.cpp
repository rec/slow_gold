#include "rec/slow/callbacks/InstanceCallbacks.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/Gain.h"
#include "rec/base/Trans.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/SetupPage.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/callbacks/SaveFile.h"
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Viewport.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::widget::waveform;

namespace {
// Skin

Trans NO_DOWNLOAD_FOUND("Your Version Of SlowGold Is Up-To-Date");
Trans NO_DOWNLOAD_FOUND_FULL("Your version of SlowGold, %s, is up-to-date.");
Trans OK("OK");


static const int SELECTION_WIDTH_PORTION = 20;

void aboutThisProgram(Instance* i) {
  i->window_->startAboutWindow();
}

void addLoopPoint(Instance* i) {
  widget::waveform::addLoopPointToViewport(i->file(), i->player_->getTime());
}

void nudgeVolumeDownOp(audio::Gain* gain) {
  if (!(gain->dim() || gain->mute()))
    gain->set_gain(gain->gain() - 1.0);
}

void nudgeVolumeDown(Instance* i) {
  data::apply(nudgeVolumeDownOp, i->file());
}

void nudgeVolumeUp(Instance* i) {
  audio::Gain gain(data::getProto<audio::Gain>(i->file()));
  if (!(gain.dim() || gain.mute())) {
    gain.set_gain(gain.gain() + 1.0);
    data::setProto(gain, i->file());
  }
}

void clearLoops(Instance *i) {
  const VirtualFile& f = i->file();
  Viewport viewport;
  LoopPointList* loops = viewport.mutable_loop_points();
  LoopPoint* loop = loops->add_loop_point();
  loop->set_selected(true);
  loop->set_time(0);
  loops->set_length(data::getProto<Viewport>(f).loop_points().length());
  data::setProto(viewport, f);
}

void clearNavigator(Instance *) { data::setProto(VirtualFileList(), data::global()); }

void dimVolumeToggle(Instance* i) {
  audio::Gain gain(data::getProto<audio::Gain>(i->file()));
  gain.set_dim(!gain.dim());
  data::setProto(gain, i->file());
}

void muteVolumeToggle(Instance* i) {
  audio::Gain gain(data::getProto<audio::Gain>(i->file()));
  gain.set_mute(!gain.mute());
  data::setProto(gain, i->file());
}

void resetGainToUnity(Instance* i) {
  audio::Gain gain(data::getProto<audio::Gain>(i->file()));
  gain.set_gain(0);
  data::setProto(gain, i->file());
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
  juce::DialogWindow::showModalDialog(Trans("Select keyboard mappings"),
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
  juce::DialogWindow::showModalDialog(Trans("Select MIDI mappings"),
                                      &comp, NULL, juce::Colours::white,
                                      true, true, true);
  data::setProto(i->target_->midiCommandMap()->getProto(), data::global());
}


void nudgeBeginLeft(Instance*) {
}

void nudgeBeginRight(Instance*) {
}

void nudgeEndLeft(Instance*) {
}

void nudgeEndRight(Instance*) {
}

void treeClose(Instance*) {
}

void treeDown(Instance*) {
}

void treeLeft(Instance*) {
}

void treeOpen(Instance*) {
}

void treeRight(Instance*) {
}

void treeUp(Instance*) {
}

void zoomOut(Instance* i) {
  widget::waveform::zoomScale(i->file(), i->length(), -1.0);
}

void zoomOutFull(Instance* i) {
  widget::waveform::zoomOutFull(i->file(), i->length());
}

void zoomToSelection(Instance* i) {
  block::Block range = block::toBlock(i->currentTime_->timeSelection());
  int64 pad = block::getSize(range) / SELECTION_WIDTH_PORTION;
  widget::waveform::zoomTo(i->file(),
                           std::max(0LL, range.first - pad),
                           std::min(i->length().get(), range.second + pad),
                           i->length());
}

void audioPreferences(Instance* i) {
  i->device_->setupPage_->show(i->components_->mainPage_->panel());
}

void closeFile(Instance* i) {
  (*i->currentFile_)(VirtualFile());
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

void checkForUpdates(Instance * i) {
  if (i->window_->application()->checkForUpdates() == app::DOWNLOAD_NOT_FOUND) {
    String msg = String::formatted(NO_DOWNLOAD_FOUND_FULL,
                                   c_str(i->window_->application()->version()));
    AlertWindow::showMessageBox(AlertWindow::InfoIcon, NO_DOWNLOAD_FOUND,
                                msg, OK);
  }
}

}  // namespace

using namespace rec::command;

void addInstanceCallbacks(CommandRecordTable* c, Instance* i) {
  using namespace rec::gui;
  using rec::gui::audio::SetupPage;
  using rec::audio::source::Player;

  addCallback(c, Command::ABOUT_THIS_PROGRAM, aboutThisProgram, i);
  addCallback(c, Command::ADD_LOOP_POINT, addLoopPoint, i);
  addCallback(c, Command::AUDIO_PREFERENCES, audioPreferences, i);
  addCallback(c, Command::CLEAR_LOOPS, clearLoops, i);
  // addCallback(c, Command::CLEAR_NAVIGATOR, clearNavigator, i);
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
  addCallback(c, Command::SAVE_FILE, saveFile, i);
  addCallback(c, Command::SAVE_FILE_SELECTION, saveFileSelection, i);
  addCallback(c, Command::TOGGLE_START_STOP, toggleStartStop, i);
  addCallback(c, Command::ZOOM_OUT, zoomOut, i);
  addCallback(c, Command::ZOOM_OUT_FULL, zoomOutFull, i);
  addCallback(c, Command::ZOOM_TO_SELECTION, zoomToSelection, i);
  addCallback(c, Command::CHECK_FOR_UPDATES, checkForUpdates, i);
}

void InstanceCallbacks::translateAll() {
  NO_DOWNLOAD_FOUND.translate();
  NO_DOWNLOAD_FOUND_FULL.translate();
  OK.translate();
}

}  // namespace slow
}  // namespace rec
