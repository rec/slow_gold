#include "rec/slow/callbacks/SaveFile.h"

#include "rec/audio/format/Manager.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/base/Trans.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Math.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace slow {
namespace {

using namespace juce;

Trans FILE_SAVE_FAILED("Error During Save.");
Trans FILE_SAVE_FAILED_FULL("There was an error saving your file %s.");
Trans FINISHING_LOADING("Finishing loading audio from disk.");
Trans SAVING_FILE("Saving File %s.");
Trans SELECT_SAVE_FILE("Choose File To Save to");
Trans DOWN("down");
Trans UP("up");
Trans OK("OK");

Trans TRANSPOSE_ONE("one semitone %s");
Trans TRANSPOSE_MANY("%s %s semitones");
Trans CANCEL("Cancel");

// Skin
const int COPY_UPDATE_SIZE = 2048;
const int COPY_BLOCK_SIZE = 2048;

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

class SaveThread : public ThreadWithProgressWindow {
 public:
  SaveThread(const String& name, Instance* i, const File& f, audio::Source* s)
      : ThreadWithProgressWindow(name, true, true),
        instance_(i), file_(f), source_(s) {
  }
  virtual ~SaveThread() {}

  virtual void run() {
#if 0
    const block::Fillable& buffer =
      *instance_->bufferFiller_->trackBuffer()->reader();

    setProgress(0.0);
    setStatusMessage(FINISHING_LOADING);
    while (!(threadShouldExit() || buffer.isFull())) {
      setProgress(buffer.filledPercent());
      Thread::sleep(100);
    }

    ptr<AudioFormatWriter> writer(audio::format::createWriter(file_));
    if (!writer) {
      LOG(DFATAL) << "Couldn't create AudioFormatWriter for " << str(file_);
      return;
    }

    setProgress(0.0);
    source_->prepareToPlay(COPY_BLOCK_SIZE, 44100.0);
    for (Samples<44100> toCopy = source_->getTotalLength();
         !threadShouldExit() && toCopy > 0; toCopy -= COPY_UPDATE_SIZE) {
      if (!writer->writeFromAudioSource(*source_,
                                        std::min(COPY_UPDATE_SIZE, toCopy.toInt()),
                                        COPY_BLOCK_SIZE)) {
        writer.reset();
        file_.deleteFile();
        String error = String::formatted(FILE_SAVE_FAILED_FULL,
                                         c_str(file_.getFileName()));
        AlertWindow::showMessageBox(AlertWindow::InfoIcon, FILE_SAVE_FAILED,
                                    error, OK);
      }
    }
#endif
  }

 private:
  Instance* const instance_;
  const File file_;
  ptr<audio::Source> source_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SaveThread)
};

}  // namespace

void saveFile(Instance* instance, const String& suffix, bool useSelection) {
  using namespace juce;
  File file = getSaveFile(instance, suffix);
  if (file != File::nonexistent) {
    ptr<audio::Source> s(instance->makeSource());
    s.reset(instance->player_->makeSourceCopy(s.transfer(), useSelection));
    String name = String::formatted(SAVING_FILE, c_str(file.getFileName()));
    SaveThread(name, instance, file, s.transfer()).runThread();
  }
}

void SaveFile::translateAll() {
  FILE_SAVE_FAILED.translate();
  FILE_SAVE_FAILED_FULL.translate();
  FINISHING_LOADING.translate();
  SAVING_FILE.translate();
  SELECT_SAVE_FILE.translate();
  OK.translate();
  DOWN.translate();
  UP.translate();
  TRANSPOSE_ONE.translate();
  TRANSPOSE_MANY.translate();
  CANCEL.translate();
}

}  // namespace slow
}  // namespace rec
