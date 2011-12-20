#include "rec/slow/CurrentFile.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Menus.h"
#include "rec/slow/Threads.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

CurrentFile::CurrentFile(Instance* i) : HasInstance(i) {
  setFile(data::getGlobal<VirtualFile>());
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
  gui::addRecentFile(file_, data::get<music::Metadata>(&file_));
  setFile(f);
  data::setProto(f, data::global());
}

void CurrentFile::setFile(const VirtualFile& f) {
  if (player())
    player()->clear();

  VirtualFile oldFile;
  {
    Lock l(lock_);
    oldFile = file_;
    file_ = f;
  }

  bool isEmpty = file::empty(file_);
  if (components()) {
    components()->directoryTree_->refreshNode(oldFile);
    components()->directoryTree_->refreshNode(f);
  }

  Samples<44100> length;
  if (isEmpty) {
    length = 0;
  } else {
    using audio::util::ThumbnailBuffer;

    ThumbnailBuffer* thumbnail = bufferFiller()->thumbnailBuffer();
    length = thumbnail->setReader(file_, music::createMusicFileReader(file_));

    if (!length) {
      LOG(DFATAL) << "Unable to read file " << getFullDisplayName(file_);
      return;
    }

    LoopPointList lpl = data::getProto<LoopPointList>(&file_);
    if (lpl.length() != length || !lpl.loop_point_size()) {
      lpl.set_length(length);
      if (!lpl.loop_point_size())
        lpl.add_loop_point()->set_selected(true);
      data::setProto(lpl, file_);
    }
  }

  {
    Lock l(lock_);
    length_ = length;
  }

  if (threads())
    threads()->fillThread()->notify();

  if (menus())
    menus()->menuItemsChanged();
}

}  // namespace slow
}  // namespace rec

