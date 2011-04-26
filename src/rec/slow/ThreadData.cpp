#include "rec/slow/ThreadData.h"
#include "rec/audio/util/FileBuffer.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;

void setVirtualFile(Instance* i, const VirtualFile& f, const StretchLoop& s) {
  ptr<FileBuffer> buffer(new FileBuffer(f));
  ThreadData* threadData = i->threads_->data();
  if (!buffer->buffer_)
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);

  else if (threadData->fileBuffer_.next())
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);

  else
	  i->components_->songData_.setFile(f);
}

void setStretch(Instance* i, const VirtualFile& f, const StretchLoop& s) {

}

void updateParameters(Instance* i) {
  ThreadData* threadData = i->threads_->data();
  VirtualFile file;
  if (threadData->fileLocker_.readAndClearChanged(&file)) {
    StretchLoop loop = persist::get<StretchLoop>(file);
    threadData->stretchLocker_.initialize(loop);
    setVirtualFile(i, file, loop);
  } else {
    StretchLoop stretch;
    if (threadData->stretchLocker_.readAndClearChanged(&stretch))
      setStretch(i, file, stretch);
  }
}

}  // namespace slow
}  // namespace rec

