#include "rec/slow/ThreadData.h"
#include "rec/audio/util/FileBuffer.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;

void setVirtualFile(Instance* i, const VirtualFile& f) {
  DLOG(INFO) << "SetVirtualFile";
  ptr<FileBuffer> buffer(new FileBuffer(f));
  ThreadData* threadData = i->threads_->data();
  if (!buffer->buffer_) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  Switcher<FileBuffer>* switcher = &threadData->fileBuffer_;
  if (switcher->next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }

  buffer->thumbnail_->addListener(i->listeners_.get());
  (*i->listeners_)(buffer->thumbnail_->thumbnail());
  switcher->setNext(buffer.transfer());
  i->threads_->data()->fetchThread_->notify();
  i->components_->songData_.setFile(f);
  // TODO persist::getData<
}

void setStretch(Instance* i, const VirtualFile& f, const Stretch& s) {
}

void updateParameters(Instance* i) {
  ThreadData* threadData = i->threads_->data();
  VirtualFile file;
  if (threadData->fileLocker_.readAndClearChanged(&file)) {
    threadData->stretchLocker_.set(persist::get<Stretch>(file));
    setVirtualFile(i, file);
  } else {
    Stretch stretch;
    if (threadData->stretchLocker_.readAndClearChanged(&stretch))
      setStretch(i, file, stretch);
  }
}

}  // namespace slow
}  // namespace rec

