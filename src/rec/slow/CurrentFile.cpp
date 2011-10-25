#include "rec/slow/CurrentFile.h"
#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/gui/DropFiles.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/Model.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (dropFiles.target_ == &components()->waveform_) {
    if (files.file_size() >= 1)
      model()->setFile(files.file(0));

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

void CurrentFile::setFile(const VirtualFile& f, const VirtualFile& oldFile) {
  file_ = f;
  player()->clear();
  audio::util::ThumbnailBuffer* thumbnailBuffer = model()->thumbnailBuffer();

  components()->playerController_.clearLevels();
  components()->directoryTree_.refreshNode(oldFile);

  bool isEmpty = file::empty(f);
  components()->waveform_.setEmpty(isEmpty);

  model()->setFileVariable(f);
  components()->directoryTree_.refreshNode(f);
  data::set(f);

  if (isEmpty)
    return;

  if (!thumbnailBuffer->setReader(f, music::createMusicFileReader(f))) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  LoopPointList loopPointList = data::get<LoopPointList>(f);
  if (!loopPointList.loop_point_size()) {
    loopPointList.add_loop_point()->set_selected(true);
    RealTime time = Samples<44100>(thumbnailBuffer->buffer()->length());
    loopPointList.add_loop_point()->set_time(time);
  }
  data::set(loopPointList, f);

  threads()->fillThread()->notify();
}

}  // namespace slow
}  // namespace rec

