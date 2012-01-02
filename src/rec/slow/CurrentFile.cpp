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

namespace rec {
namespace slow {

class FileDataListener : public data::GlobalDataListener<VirtualFile> {
 public:
  explicit FileDataListener(CurrentFile* f) : parent_(f) {}
  virtual void operator()(const VirtualFile& f) {
    parent_->setFile(f);
  }

 private:
  CurrentFile* const parent_;
};


CurrentFile::CurrentFile(Instance* i) : HasInstance(i), initialized_(false) {
  fileListener_.reset(new FileDataListener(this));
  fileListener_->startListening();
}

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
#if 0
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
#endif
  if (files.file_size() >= 1)
    (*this)(files.file(0));
}

void CurrentFile::operator()(const VirtualFile& f) {
  setFile(f);
  data::setProto(f, data::global());
}

void CurrentFile::setFile(const VirtualFile& f) {
  if (initialized_) {
    Lock l(lock_);
    if (data::equals(f, file_))
      return;
  } else {
    initialized_ = true;
  }

  if (player())
    player()->clear();

  gui::addRecentFile(file_, data::get<music::Metadata>(&file_));
  VirtualFile oldFile;
  {
    Lock l(lock_);
    oldFile = file_;
    file_ = f;
  }

  Samples<44100> length(0);

  bool fileEmpty = file::empty(file_);

  if (!fileEmpty) {
    using audio::util::TrackBufferAndThumbnail;

    TrackBufferAndThumbnail* thumbnail = bufferFiller()->trackBuffer();
    length = thumbnail->setReader(file_, music::createMusicFileReader(file_));
  }

  if (length) {
    LoopPointList lpl = data::getProto<LoopPointList>(&file_);
    if (lpl.length() != length || !lpl.loop_point_size()) {
      lpl.set_length(length);
      if (!lpl.loop_point_size())
        lpl.add_loop_point()->set_selected(true);
      data::setProto(lpl, file_);
    }
    for (int i = 0; i < lpl.loop_point_size(); ++i) {
      if (lpl.loop_point(i).selected()) {
        Samples<44100> t = lpl.loop_point(i).time();
        currentTime()->jumpToTime(t);
        (*currentTime())(t);
      }
    }

  } else if (!fileEmpty) {
    String s = file::getDisplayName(file_);
    (*this)(file::none());
    currentTime()->jumpToTime(0);
    (*currentTime())(0);

    juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                      "File does not exist or can't be read",
                                      "File " + s + " does not exist or can't be read as an audio file.",
                                      "", window());
    return;
  }

  {
    Lock l(lock_);
    length_ = length;
  }

  components()->setEnabled(length);
  components()->directoryTree_->refreshNode(oldFile);
  components()->directoryTree_->refreshNode(f);

  if (threads())
    threads()->fillThread()->notify();

  if (menus())
    menus()->menuItemsChanged();
}

}  // namespace slow
}  // namespace rec

