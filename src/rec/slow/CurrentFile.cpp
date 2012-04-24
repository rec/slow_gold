#include "rec/slow/CurrentFile.h"

#include "rec/audio/source/Player.h"
#include "rec/audio/util/TrackBufferAndThumbnail.h"
#include "rec/command/Command.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::widget::waveform;

class FileDataListener : public data::GlobalDataListener<VirtualFile> {
 public:
  explicit FileDataListener(CurrentFile* f) : parent_(f) {}
  virtual void operator()(const VirtualFile& f) {
    parent_->setFile(f);
  }

 private:
  CurrentFile* const parent_;
};

CurrentFile::CurrentFile(Instance* i) : HasInstance(i),
                                        initialized_(false),
                                        empty_(true),
                                        hasStarted_(false) {
  fileListener_.reset(new FileDataListener(this));
}

void CurrentFile::init() {
  fileListener_->init();
}

CurrentFile::~CurrentFile() {}

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (files.file_size() >= 1)
    (*this)(files.file(0));
}

void CurrentFile::setFileAndData(const VirtualFile& f) {
  FileResult result = setFile(f);
  if (result != NO_CHANGE)
    data::setProto(result ? f : VirtualFile(), data::global());
}

CurrentFile::FileResult CurrentFile::setFile(const VirtualFile& f) {
  Lock l(instance_->lock_);
  if (!initialized_)
    initialized_ = true;
  else if (data::equals(f, file_))
    return NO_CHANGE;

  if (player())
    player()->reset();

  if (!empty_)
    gui::addRecentFile(file_, data::get<music::Metadata>(&file_));

  VirtualFile oldFile;
  oldFile = file_;
  file_ = f;

  Samples<44100> length(0);
  FileResult result = GOOD_FILE;

  empty_ = file::empty(file_);
  if (empty_) {
    result = EMPTY_FILE;
  } else {
    music::MusicFileReader musicReader(file_);
    if (musicReader.empty()) {
      empty_ = true;
    } else {
      length = bufferFiller()->setReader(file_, musicReader.transfer());
      if (!length) {
        musicReader.setError("Ran Out Of Memory For Your File",
                             "Your file was so large that the program "
                             "ran out of memory.");
        empty_ = true;
      }
    }

    if (empty_) {
      result = ERROR_FILE;
      if (hasStarted_) {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                          musicReader.errorTitle(),
                                          musicReader.errorDetails());
      }
      file_.Clear();
    }
  }

  if (!empty_) {
    LoopPointList lpl = data::getProto<LoopPointList>(&file_);
    if (lpl.length() != length || !lpl.loop_point_size()) {
      lpl.set_length(length);
      if (!lpl.loop_point_size())
        lpl.add_loop_point()->set_selected(true);
      data::setProto(lpl, file_);
    }
    currentTime()->jumpToTime(0);
    (*currentTime())(0);
  }

  length_ = length;

  Zoom zoom = data::getProto<Zoom>(&file_);
  (*components()->waveform_)(zoom);
  (*currentTime())(zoom);

  components()->setEnabled(length);
  components()->directoryTree_->refreshNode(oldFile);
  components()->directoryTree_->refreshNode(f);

  if (menus())
    menus()->menuItemsChanged();

  return result;
}

}  // namespace slow
}  // namespace rec

#if 0

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (components()->directoryTree_->treeView()->isTreeDrop(dropFiles.target_)) {
    using file::getFile;

    typedef std::set<string> FileSet;
    FileSet existing;
    VirtualFileList list(data::getGlobal<file::VirtualFileList>());
    for (int i = 0; i < list.file_size(); ++i)
      existing.insert(str(getFile(list.file(i)).getFullPathName()));

    for (int i = 0; i < files.file_size(); ++i) {
      if (existing.find(str(getFile(files.file(i)).getFullPathName())) == existing.end())
        data::editable<VirtualFileList>()->append(files.file(i), data::Address("file"));
    }
  } else {
  }
  if (files.file_size() >= 1)
    (*this)(files.file(0));
}

#endif

