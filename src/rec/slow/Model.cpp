#include "rec/slow/Model.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;

static const int PARAMETER_WAIT = 100;
static const int PRELOAD = 10000;

Model::Model(Instance* i) : HasInstance(i),
                            fileLocker_(&lock_),
                            stretchLocker_(&lock_),
                            loopLocker_(&lock_),
                            nextPosition_(-1) {
  persist::setter<VirtualFile>()->addListener(&fileLocker_);
}

void Model::fillOnce() {
  thumbnailBuffer_.switchIfNext();
  ThumbnailBuffer* buffer = thumbnailBuffer_.current();
  if (!buffer || buffer->isFull()) {
    Thread::getCurrentThread()->wait(PARAMETER_WAIT);
  } else {
    buffer->fillNextBlock();
    if (nextPosition_ != -1)
      setNextPosition(nextPosition_);
  }
}

void Model::setNextPosition(SampleTime pos) {
  {
    ScopedLock l(lock_);
    ThumbnailBuffer* buffer = thumbnailBuffer_.current();
    if (!buffer || buffer->hasFilled(block::Block(pos, pos + PRELOAD))) {
      nextPosition_ = -1;
    } else {
      nextPosition_ = pos;
      if (buffer)
        buffer->setPosition(pos);
      return;
    }
  }
  (*listeners())(pos);
}

void Model::operator()(const VirtualFile& f) {
  if (thumbnailBuffer_.next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }

  ptr<ThumbnailBuffer> buffer(new ThumbnailBuffer(f));

  buffer->thumbnail()->addListener(&components()->waveform_);
  player()->setSource(new BufferSource(*buffer->buffer()));
  thumbnailBuffer_.setNext(buffer.transfer());
  threads()->fetchThread()->notify();

  persist::Data<LoopPointList>* setter = persist::setter<LoopPointList>(f);
  components()->loops_.setData(setter);

  stretchLocker_.listenTo(persist::setter<Stretch>(f));
  loopLocker_.listenTo(setter);

  stretchLocker_.set(persist::get<Stretch>(f));
  loopLocker_.set(persist::get<LoopPointList>(f));

  components()->songData_.setFile(f);
}

void Model::checkChanged() {
  fileLocker_.broadcastIfChanged(this); // TODO
  stretchLocker_.broadcastIfChanged(listeners());
  loopLocker_.broadcastIfChanged(listeners());
}

}  // namespace slow
}  // namespace rec
