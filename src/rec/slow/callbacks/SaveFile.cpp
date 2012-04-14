#include "rec/slow/callbacks/SaveFile.h"

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

Trans FINISHING_LOADING("Finishing loading audio from disk.");
Trans SAVING_FILE("Saving file %s.");
Trans SELECT_SAVE_FILE("Choose File To Save to");
Trans DOWN("down");
Trans UP("up");

Trans TRANSPOSE_ONE("one semitone %s");
Trans TRANSPOSE_MANY("%s %s semitones");
Trans CANCEL("Cancel");

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
  Callback(bool* cancelled) : cancelled_(cancelled) {}
  virtual ~Callback() {}
  virtual void modalStateFinished (int returnValue) {
    DLOG(INFO) << "Here!!";
    *cancelled_ = true;
  }

 private:
  bool* const cancelled_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Callback)
};

}  // namespace

void saveFile(Instance* instance, const String& suffix, bool useSelection) {
  using namespace juce;
  File file = getSaveFile(instance, suffix);
  if (file == File::nonexistent) {
    DLOG(INFO) << "none!";
    return;
  }

  AlertWindow alert(FINISHING_LOADING, FINISHING_LOADING,
                    AlertWindow::InfoIcon);
  alert.addButton(CANCEL, 1, KeyPress(KeyPress::escapeKey));
  double progress = 0.0;
  bool cancelled = false;
  alert.addProgressBarComponent(progress);
  alert.enterModalState(true, new Callback(&cancelled));

  const block::Fillable& buffer =
    *instance->bufferFiller_->trackBuffer()->buffer();

  DLOG(INFO) << "Starting to wait";
  while (!(cancelled || buffer.isFull())) {
    progress = buffer.filledPercent();
    Thread::sleep(500);
  }
  DLOG(INFO) << "First loop done";
  while (!cancelled) {
    Thread::sleep(500);
  }
  DLOG(INFO) << "Second loop done";
}

void SaveFile::translateAll() {
  FINISHING_LOADING.translate();
  SAVING_FILE.translate();
  SELECT_SAVE_FILE.translate();
  DOWN.translate();
  UP.translate();
  TRANSPOSE_ONE.translate();
  TRANSPOSE_MANY.translate();
  CANCEL.translate();
}

}  // namespace slow
}  // namespace rec
