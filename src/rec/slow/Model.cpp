#include "rec/slow/Model.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Threads.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;

static const int PARAMETER_WAIT = 100;
static const int PRELOAD_SIZE = 10000;

Model::Model(Instance* i) : HasInstance(i),
                            fileLocker_(&lock_),
                            stretchLocker_(&lock_),
                            loopLocker_(&lock_),
                            nextPosition_(-1) {
  persist::setter<VirtualFile>()->addListener(&fileLocker_);
}

void Model::fillOnce() {
  fileBuffer_.switchIfNext();
  FileBuffer* buffer = fileBuffer_.current();
  if (!buffer || !buffer->buffer_ || buffer->buffer_->isFull()) {
    Thread::getCurrentThread()->wait(PARAMETER_WAIT);
  } else {
    buffer->buffer_->fillNextBlock();
    if (nextPosition_ != -1)
      setNextPosition(nextPosition_);
  }
}

bool Model::hasNextPosition(SampleTime pos) {
  FileBuffer* buffer = fileBuffer_.current();
  if (!buffer || !buffer->buffer_)
    return true;

  block::Block b(pos, pos + PRELOAD_SIZE);
  bool result = buffer->buffer_->hasFilled(b);
  DLOG(INFO) << pos << ", " << result;
  return result;
}

void Model::setNextPosition(SampleTime pos) {
  {
    ScopedLock l(lock_);
    if (hasNextPosition(pos)) {
      nextPosition_ = -1;
    } else {
      nextPosition_ = pos;
      return;
    }
  }
  (*listeners())(pos);
}

void Model::operator()(const VirtualFile& f) {
  if (fileBuffer_.next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }

  ptr<FileBuffer> buf(new FileBuffer(f));
  if (!buf->buffer_) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  buf->thumbnail_->addListener(&components()->waveform_);
  player()->setSource(new BufferSource(*buf->buffer_->buffer()));
  fileBuffer_.setNext(buf.transfer());
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
