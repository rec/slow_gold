#include "rec/slow/callbacks/SaveFile.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/format/Manager.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/base/Trans.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/slow/GuiSettings.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Math.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace slow {
namespace {

using namespace juce;
using audio::AudioSettings;
using namespace rec::audio::stretch;

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
Trans CANT_CHANGE_SUFFIX("The file extension must be %s - "
                         "please don't change it.");

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
                 const GuiSettings& guiSettings,
                 const AudioSettings& audioSettings) {
  File file;
  if (guiSettings.has_last_directory())
    file = str(guiSettings.last_directory());
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

  double ps = audio::stretch::pitchSemitones(stretch,
                                             audioSettings.master_tune());
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

static const char* SUFFIXES[] = {".aiff", ".flac", ".ogg", ".wav"};

File getSaveFile(Instance* instance, audio::AudioSettings::FileType t) {
  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  if (instance->empty())
    return File::nonexistent;

  String suffix = SUFFIXES[t];
  File file;
  GuiSettings settings = data::getGlobal<GuiSettings>();
  audio::AudioSettings audioSettings = data::getGlobal<audio::AudioSettings>();
  File startFile = getBaseFile(instance, suffix, settings, audioSettings);

  while (true) {
    file = slow::browseForFile(SELECT_SAVE_FILE, startFile, slow::SAVE_FILE);
    if (file == File::nonexistent)
      return file;
    if (file.getFileExtension() == suffix)
      break;
    String error = String::formatted(CANT_CHANGE_SUFFIX, c_str(suffix));
    AlertWindow::showMessageBox(AlertWindow::InfoIcon, error, error, OK);
  }

  settings.set_last_directory(str(file.getParentDirectory()));
  data::setGlobal(settings);

  return file;
}

class SaveThread : public ThreadWithProgressWindow {
 public:
  SaveThread(const String& name, Instance* i, const File& f, audio::Source* s,
             Samples<44100> length)
      : ThreadWithProgressWindow(name, true, true),
        instance_(i), file_(f), source_(s), length_(length) {
  }
  virtual ~SaveThread() {}

  virtual void run() {
    const block::Fillable& buffer = *instance_->bufferFiller_->reader();

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
    String name = file_.getFileName();
    setStatusMessage(String::formatted(SAVING_FILE, c_str(name)));

    for (Samples<44100> toCopy = length_;
         !threadShouldExit() && toCopy > 0; toCopy -= COPY_UPDATE_SIZE) {
      if (writer->writeFromAudioSource(*source_,
                                        std::min(COPY_UPDATE_SIZE, toCopy.toInt()),
                                        COPY_BLOCK_SIZE)) {
        setProgress(1.0 - toCopy / (1.0 * length_));
      } else {
        writer.reset();
        file_.deleteFile();
        String error = String::formatted(FILE_SAVE_FAILED_FULL,
                                         c_str(file_.getFileName()));
        AlertWindow::showMessageBox(AlertWindow::InfoIcon, FILE_SAVE_FAILED,
                                    error, OK);
      }
    }
  }

 private:
  Instance* const instance_;
  const File file_;
  ptr<audio::Source> source_;
  const Samples<44100> length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SaveThread)
};

void doSaveFile(Instance* instance, bool useSelection) {
  using namespace juce;

  AudioSettings::FileType t = data::getGlobal<AudioSettings>().file_type_for_save();
  File file = getSaveFile(instance, t);
  if (file != File::nonexistent) {
    ptr<audio::Source> s(instance->makeSource());
    s.reset(instance->player_->makeSourceCopy(s.transfer(), useSelection));
    String name = String::formatted(SAVING_FILE, c_str(file.getFileName()));
    Samples<44100> len = useSelection ?
      instance->player_->getSelectionLength() : Samples<44100>(s->getTotalLength());
    SaveThread(name, instance, file, s.transfer(), len).runThread();
  }
}

}  // namespace


void saveFile(Instance* instance) {
  doSaveFile(instance, false);
}

void saveFileSelection(Instance* instance) {
  doSaveFile(instance, true);
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
  CANT_CHANGE_SUFFIX.translate();
}

}  // namespace slow
}  // namespace rec
