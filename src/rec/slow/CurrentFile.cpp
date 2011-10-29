#include "rec/slow/CurrentFile.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/data/Data.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  DLOG(INFO) << "DropFiles";
  const file::VirtualFileList& files = dropFiles.files_;
  if (dropFiles.target_ == &components()->waveform_) {
    if (files.file_size() >= 1)
      data::set(files.file(0));

    LOG_IF(ERROR, files.file_size() != 1);

  } else if (dropFiles.target_ == components()->directoryTree_.treeView()) {
    using file::getFile;

    typedef std::set<string> FileSet;
    FileSet existing;
    VirtualFileList list(data::get<file::VirtualFileList>());
    for (int i = 0; i < list.file_size(); ++i)
      existing.insert(str(getFile(list.file(i)).getFullPathName()));

    for (int i = 0; i < files.file_size(); ++i) {
      if (existing.find(str(getFile(files.file(i)).getFullPathName())) == existing.end())
        data::editable<VirtualFileList>()->append(files.file(i), data::Address("file"));
    }
  }
}

void CurrentFile::operator()(const VirtualFile& f) {
  player()->clear();

  VirtualFile oldFile;
  {
    Lock l(lock_);
    oldFile = file_;
    file_ = f;
  }

  components()->playerController_->clearLevels();
  components()->directoryTree_.refreshNode(oldFile);

  bool isEmpty = file::empty(f);
  components()->waveform_.setEmpty(isEmpty);
  components()->directoryTree_.refreshNode(f);

  if (isEmpty) {
    components()->waveform_.setLength(0);
  } else {
    using audio::util::ThumbnailBuffer;

    ThumbnailBuffer* thumbnailBuffer = bufferFiller()->thumbnailBuffer();
    if (!thumbnailBuffer->setReader(f, music::createMusicFileReader(f))) {
      LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
      return;
    }
    components()->waveform_.setLength(thumbnailBuffer->buffer()->length());
    threads()->fillThread()->notify();
  }
}

}  // namespace slow
}  // namespace rec

