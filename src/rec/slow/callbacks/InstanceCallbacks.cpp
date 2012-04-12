#include "rec/slow/callbacks/InstanceCallbacks.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/app/GenericApplication.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Gain.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/SetupPage.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Math.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::widget::waveform;

namespace {
// Skin

Trans FINISHING_LOADING("Finishing loading audio from disk.");
Trans SAVING_FILE("Saving file %s.");
Trans SELECT_SAVE_FILE("Choose File To Save to");
Trans DOWN("down");
Trans UP("up");

Trans TRANSPOSE_ONE("one semitone %s");
Trans TRANSPOSE_MANY("%s %s semitones");

static const int SELECTION_WIDTH_PORTION = 20;

void aboutThisProgram(Instance* i) {
  i->window_->startAboutWindow();
}

void addLoopPoint(Instance* i) {
  audio::addLoopPointToData(i->file(), i->player_->getTime());
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
  LoopPointList loops;
  loops.add_loop_point();
  loops.set_length(data::getProto<LoopPointList>(f).length());
  data::setProto(loops, f);
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
  widget::waveform::zoom(i->file(), i->length(), -1.0);
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
  i->window_->application()->checkForUpdates();
}

String removeTrailingZeroes(const String& s) {
  String st = s;
  st = st.trimCharactersAtEnd("0");
  st = st.trimCharactersAtEnd(".");
  return st;
}

File getBaseFile(Instance* instance, const String& suffix,
                 const GuiSettings& settings) {
  using namespace juce;
  using namespace rec::audio::stretch;

  File file;
  if (settings.has_last_directory())
    file = str(settings.last_directory());
  else
    file = File::getSpecialLocation(File::userMusicDirectory);

  String baseName = instance->window_->getName();
  Stretch stretch = instance->player_->stretchy()->getStretch();
  double ts = 100.0 / audio::stretch::timeScale(stretch);

  if (!near(ts, 100.0, 0.05)) {
    int roundTs = static_cast<int>(ts);
    if (near(ts, roundTs, 0.05))
      baseName += String::formatted(" @ %d%%", roundTs);
    else
      baseName += String::formatted(" @ %.1f%%", ts);
  }

  double ps = audio::stretch::pitchSemitones(stretch);
  if (!near(ps, 0.0, 0.005)) {
    const Trans& sign = (ps > 0) ? UP : DOWN;
    ps = abs(ps);
    String num = removeTrailingZeroes(String::formatted("%.3f", ps));
    baseName += ", ";
    if (num == "1")
      baseName += String::formatted(TRANSPOSE_ONE, c_str(sign));
    else
      baseName += String::formatted(TRANSPOSE_MANY, c_str(sign), c_str(num));
  }

  return file.getChildFile(baseName + suffix);
}

File browseForFileToSave(const File& startFile) {
  FileChooser c(SELECT_SAVE_FILE, startFile);
  return c.browseForFileToSave(true) ? c.getResult() : File::nonexistent;
}

File browseForFileToSaveTreeView(const File& startFile) {
  int flags = FileBrowserComponent::saveMode +
    FileBrowserComponent::canSelectFiles +
    FileBrowserComponent::useTreeView;

  FileBrowserComponent fileBrowser(flags, startFile, NULL, NULL);
  FileChooserDialogBox dialogBox(SELECT_SAVE_FILE, "", fileBrowser, true,
                                 Colours::white);
  return dialogBox.show() ? fileBrowser.getSelectedFile(0) : File::nonexistent;
}

File getSaveFile(Instance* instance, const String& suffix) {
  File file;
  if (instance->empty())
    return file;

  GuiSettings settings = data::getGlobal<GuiSettings>();
  File startFile = getBaseFile(instance, suffix, settings);
  file = settings.use_tree_view_in_file_dialogs() ?
    browseForFileToSave(startFile) : browseForFileToSaveTreeView(startFile);

  if (file != File::nonexistent) {
    settings.set_last_directory(str(file.getParentDirectory()));
    data::setGlobal(settings);
  }
  return file;
}

class Callback : public ModalComponentManager::Callback {
 public:
  Callback() {}
  virtual ~Callback() {}
  virtual void modalStateFinished (int returnValue) {
    DLOG(INFO) << "Here! " << returnValue;
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Callback)
};

void save(Instance* instance, const String& suffix, bool useSelection) {
  using namespace juce;
  File file = getSaveFile(instance, suffix);
  if (file == File::nonexistent) {
    DLOG(INFO) << "none!";
    return;
  }

  AlertWindow alert(FINISHING_LOADING, FINISHING_LOADING,
                    AlertWindow::InfoIcon);
  double progress = 0.0;
  alert.addProgressBarComponent(progress);
  alert.enterModalState(true, new Callback);
  Thread::sleep(5000);
  DLOG(INFO) << str(file);

}

void saveAsAIFF(Instance* i) { save(i, ".aiff", false); }
void saveAsFLAC(Instance* i) { save(i, ".flac", false); }
void saveAsMP3(Instance* i) { save(i, ".mp3", false); }
void saveAsOGG(Instance* i) { save(i, ".ogg", false); }
void saveAsWAV(Instance* i) { save(i, ".wav", false); }

void saveSelectionAsAIFF(Instance* i) { save(i, ".aiff", true); }
void saveSelectionAsFLAC(Instance* i) { save(i, ".flac", true); }
void saveSelectionAsMP3(Instance* i) { save(i, ".mp3", true); }
void saveSelectionAsOGG(Instance* i) { save(i, ".ogg", true); }
void saveSelectionAsWAV(Instance* i) { save(i, ".wav", true); }

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
  addCallback(c, Command::SAVE_AS_AIFF, saveAsAIFF, i);
  addCallback(c, Command::SAVE_AS_FLAC, saveAsFLAC, i);
  addCallback(c, Command::SAVE_AS_MP3, saveAsMP3, i);
  addCallback(c, Command::SAVE_AS_OGG, saveAsOGG, i);
  addCallback(c, Command::SAVE_AS_WAV, saveAsWAV, i);
  addCallback(c, Command::SAVE_SELECTION_AS_AIFF, saveSelectionAsAIFF, i);
  addCallback(c, Command::SAVE_SELECTION_AS_FLAC, saveSelectionAsFLAC, i);
  addCallback(c, Command::SAVE_SELECTION_AS_MP3, saveSelectionAsMP3, i);
  addCallback(c, Command::SAVE_SELECTION_AS_OGG, saveSelectionAsOGG, i);
  addCallback(c, Command::SAVE_SELECTION_AS_WAV, saveSelectionAsWAV, i);
  addCallback(c, Command::TOGGLE_START_STOP, toggleStartStop, i);
  addCallback(c, Command::ZOOM_OUT, zoomOut, i);
  addCallback(c, Command::ZOOM_OUT_FULL, zoomOutFull, i);
  addCallback(c, Command::ZOOM_TO_SELECTION, zoomToSelection, i);
  addCallback(c, Command::CHECK_FOR_UPDATES, checkForUpdates, i);
}

void InstanceCallbacks::translateAll() {
  FINISHING_LOADING.translate();
  SAVING_FILE.translate();
  SELECT_SAVE_FILE.translate();
  DOWN.translate();
  UP.translate();
  TRANSPOSE_ONE.translate();
  TRANSPOSE_MANY.translate();
}

}  // namespace slow
}  // namespace rec
