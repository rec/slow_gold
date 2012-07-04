#include "rec/slow/callbacks/InstanceCallbacks.h"

#include "rec/app/Files.h"
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
#include "rec/slow/callbacks/RepeatedCallbacks.h"
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

static const bool QUIT_EVEN_IF_CLEAR_FAILS = false;

Trans NO_DOWNLOAD_FOUND("Your Version Of SlowGold Is Up-To-Date");
Trans NO_DOWNLOAD_FOUND_FULL("Your version of SlowGold, %s, is up-to-date.");
Trans OK("OK");
Trans CANCEL("Cancel");

Trans CLEAR_KEYBOARD_MAPPINGS_TITLE("Clear Keyboard Mappings.");
Trans CLEAR_KEYBOARD_MAPPINGS_FULL("Clear all keyboard mappings to factory "
                                   "default?");
Trans CLEAR_MIDI_MAPPINGS_TITLE("Clear MIDI Mappings.");
Trans CLEAR_MIDI_MAPPINGS_FULL("Clear all MIDI mappings?");

Trans CONFIRM_CLEAR_ALL_SETTINGS("Clearing All Settings For All Tracks");

Trans CONFIRM_CLEAR_ALL_SETTINGS_FULL("You want to clear *all* settings, and quit "
                                      "SlowGold.  Is this OK?");

Trans CONFIRM_CLEAR_SETTINGS_FOR_THIS_TRACK("Clearing Settings For This Track Only");

Trans CONFIRM_CLEAR_SETTINGS_FOR_THIS_TRACK_FULL("You want to clear settings for this "
                                                 "track only, and quit the "
                                                 "program.  Is this OK?");

Trans CLEAR_FAILED("Unable To Clear Settings");

Trans CLEAR_FAILED_FULL("Sorry, there was an error clearing the settings. "
                        "Please report this to support@worldwidewoodshed.com.");

static const int SELECTION_WIDTH_PORTION = 20;

void aboutThisProgram(Instance* i) {
  i->window_->startAboutWindow();
}

void addLoopPoint(Instance* i) {
  widget::waveform::addLoopPointToViewport(i->file(),
                                           i->player_->getTime());
}

using namespace rec::audio;
using namespace rec::audio::stretch;

bool nudgeVolume(Gain* gain, bool isInc) {
  if (gain->dim() || gain->mute())
    return false;

  double inc = data::getGlobal<AudioSettings>().volume_nudge_db();
  gain->set_gain(gain->gain() + (isInc ? inc : -inc));
  return true;
}

void nudgeSpeed(Stretch* stretch, bool isInc) {
  double nudge = data::getGlobal<AudioSettings>().speed_nudge_percent() / 100.0;
  double scale = isInc ? (1.0 + nudge) : 1.0 / (1.0 + nudge);
  stretch->set_time_percent(stretch->time_percent() * scale);
}

bool nudgeVolumeDown(Gain* g) { return nudgeVolume(g, false); }
bool nudgeVolumeUp(Gain* g) { return nudgeVolume(g, true); }

void nudgeSpeedDown(Stretch* s) { nudgeSpeed(s, false); }
void nudgeSpeedUp(Stretch* s) { nudgeSpeed(s, true); }

void clearLoops(Viewport* viewport) {
  LoopPointList* loops = viewport->mutable_loop_points();
  loops->mutable_loop_point()->Clear();

  LoopPoint* loop = loops->add_loop_point();
  loop->set_selected(true);
  loop->set_time(0);
}

void clearKeyboardMappings(Instance* i) {
  if (AlertWindow::showOkCancelBox(AlertWindow::InfoIcon,
                                   CLEAR_KEYBOARD_MAPPINGS_TITLE,
                                   CLEAR_KEYBOARD_MAPPINGS_FULL,
                                   OK, CANCEL)) {
    command::clearKeyboardBindings(i->target_->targetManager());

  }
}


void clearMidiMappings() {
  if (AlertWindow::showOkCancelBox(AlertWindow::InfoIcon,
                                   CLEAR_MIDI_MAPPINGS_TITLE,
                                   CLEAR_MIDI_MAPPINGS_FULL,
                                   OK, CANCEL)) {
    data::setGlobal(command::CommandMapProto());
  }
}

void clearNavigator(VirtualFileList *vfl) {
  vfl->Clear();
}

void dimVolumeToggle(Gain* gain) {
  gain->set_dim(!gain->dim());
}

void muteVolumeToggle(Gain* gain) {
  gain->set_mute(!gain->mute());
}

void resetGainToUnity(Gain* gain) {
  gain->set_gain(0);
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
  widget::waveform::zoomScale(i->file(), i->length(),
                              i->getSourceSampleRate(), -1.0);
}

void zoomOutFull(Instance* i) {
  widget::waveform::zoomOutFull(i->file(), i->length());
}

void zoomToSelection(Instance* i) {
  block::Block range = block::toBlock(i->currentTime_->timeSelection());
  int64 pad = block::getSize(range) / SELECTION_WIDTH_PORTION;
  widget::waveform::zoomTo(i->file(),
                           i->length(),
                           i->getSourceSampleRate(),
                           std::max(0LL, range.first - pad),
                           std::min(i->length().get(), range.second + pad));
}

void audioPreferences(Instance* i) {
  i->device_->setupPage_->show(i->components_->mainPage_->panel());
}

void closeFile(Instance* i) {
  i->currentFile_->setVirtualFile(data::noData(), false);
}

void open(Instance* i) {
  gui::dialog::openOneFile(i->currentFile_.get());
}

void quit(Instance* i) {
  i->window_->application()->quit();
}

void toggleStartStop(Instance* i) {
  if (!i->empty())
    i->player_->toggle();
}

void checkForUpdates(Instance* i) {
  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  if (i->window_->application()->checkForUpdates() == app::DOWNLOAD_NOT_FOUND) {
    String msg = String::formatted(NO_DOWNLOAD_FOUND_FULL,
                                   c_str(i->window_->application()->version()));
    AlertWindow::showMessageBox(AlertWindow::InfoIcon, NO_DOWNLOAD_FOUND,
                                msg, OK);
  }
}

void deleteRecursivelyAndQuit(const File& dir, Instance* i,
                              const String& title, const String& msg) {
  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  if (!AlertWindow::showOkCancelBox(AlertWindow::InfoIcon, title, msg,
                                    OK, CANCEL)) {
    return;
  }
  closeFile(i);
  bool success = dir.deleteRecursively();
  if (QUIT_EVEN_IF_CLEAR_FAILS || success) {
    i->window_->application()->quit();
  } else {
    AlertWindow::showMessageBox(AlertWindow::WarningIcon, CLEAR_FAILED,
                                CLEAR_FAILED_FULL);
  }
}

void clearAllSettings(Instance* i) {
  deleteRecursivelyAndQuit(app::getAppDirectory(), i,
                           CONFIRM_CLEAR_ALL_SETTINGS,
                           CONFIRM_CLEAR_ALL_SETTINGS_FULL);
}

void clearSettingsForThisTrack(Instance* i) {
  deleteRecursivelyAndQuit(file::getShadowDirectory(i->file()), i,
                           CONFIRM_CLEAR_SETTINGS_FOR_THIS_TRACK,
                           CONFIRM_CLEAR_SETTINGS_FOR_THIS_TRACK_FULL);
}

}  // namespace

using namespace rec::command;

void addInstanceCallbacks(CommandRecordTable* c, Instance* i) {
  using namespace rec::gui;
  using rec::gui::audio::SetupPage;
  using rec::audio::source::Player;

  addCallback(c, Command::CLEAR_MIDI_MAPPINGS, clearMidiMappings);
  addCallback(c, Command::CLEAR_KEYBOARD_MAPPINGS, clearKeyboardMappings, i);
  addCallback(c, Command::ABOUT_THIS_PROGRAM, aboutThisProgram, i);
  addCallback(c, Command::ADD_LOOP_POINT, addLoopPoint, i);
  addCallback(c, Command::AUDIO_PREFERENCES, audioPreferences, i);
  addApplyCallback(c, Command::CLEAR_LOOPS, clearLoops, i);
  addCallback(c, Command::CLEAR_ALL_SETTINGS, clearAllSettings, i);
  addCallback(c, Command::CLEAR_SETTINGS_FOR_THIS_TRACK,
              clearSettingsForThisTrack, i);
  // addCallback(c, Command::CLEAR_NAVIGATOR, clearNavigator, i);
  addCallback(c, Command::CLOSE_FILE, closeFile, i);
  addApplyCallback(c, Command::DIM_VOLUME_TOGGLE, dimVolumeToggle, i);
  addCallback(c, Command::KEYBOARD_MAPPINGS, keyboardMappings, i);
  addCallback(c, Command::MIDI_MAPPINGS, midiMappings, i);
  addApplyCallback(c, Command::MUTE_VOLUME_TOGGLE, muteVolumeToggle, i);
  addApplyCallback(c, Command::NUDGE_VOLUME_DOWN, nudgeVolume, false, i);
  addApplyCallback(c, Command::NUDGE_VOLUME_UP, nudgeVolume, true, i);
  addApplyCallback(c, Command::NUDGE_SPEED_DOWN, nudgeSpeed, false, i);
  addApplyCallback(c, Command::NUDGE_SPEED_UP, nudgeSpeed, true, i);

  addCallback(c, Command::OPEN, open, i);
  addCallback(c, Command::QUIT, quit, i);
  addApplyCallback(c, Command::RESET_GAIN_TO_UNITY, resetGainToUnity, i);
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
  CLEAR_KEYBOARD_MAPPINGS_TITLE.translate();
  CLEAR_KEYBOARD_MAPPINGS_FULL.translate();
  CLEAR_MIDI_MAPPINGS_TITLE.translate();
  CLEAR_MIDI_MAPPINGS_FULL.translate();
  CONFIRM_CLEAR_ALL_SETTINGS.translate();
  CONFIRM_CLEAR_SETTINGS_FOR_THIS_TRACK.translate();
  CONFIRM_CLEAR_ALL_SETTINGS_FULL.translate();
  CONFIRM_CLEAR_SETTINGS_FOR_THIS_TRACK_FULL.translate();
  CLEAR_FAILED.translate();
  CANCEL.translate();
}

}  // namespace slow
}  // namespace rec
