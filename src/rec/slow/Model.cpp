#include "rec/slow/Model.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/gui/audio/LoopPoint.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Threads.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;
using namespace rec::util::block;
using namespace rec::widget::waveform;

static const int PARAMETER_WAIT = 1000;
static const int PRELOAD = 10000;

Model::Model(Instance* i) : HasInstance(i),
                            fileLocker_(&lock_),
                            stretchLocker_(&lock_),
                            loopLocker_(&lock_),
                            zoomLocker_(&lock_),
                            time_(0),
                            triggerTime_(-1),
                            selectionSource_(NULL) {
  persist::setter<VirtualFile>()->addListener(&fileLocker_);
  player()->timeBroadcaster()->addListener(this);
}

void Model::fillOnce() {
  thumbnailBuffer_.switchIfNext();
  ThumbnailBuffer* buffer = thumbnailBuffer_.current();
  if (!buffer || buffer->isFull()) {
    Thread::getCurrentThread()->wait(PARAMETER_WAIT);
    return;
  }

  if (triggerTime_ == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(timeSelection_, buffer->filled());
    print(print(print(DLOG(INFO), timeSelection_) << " !", buffer->filled()) << ", ", fill);
    BlockList fillList = fillSeries(fill, time_, length());
    // DLOG_EVERY_N(INFO, 4) << selection << ", " << buffer->filled()
    // << ", " << toFill;
    if (!fillList.empty())
      buffer->setPosition(fillList.begin()->first);
  }

  buffer->fillNextBlock();
  if (triggerTime_ != -1)
    setTriggerTime(triggerTime_);
}

void Model::setTriggerTime(SampleTime pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection_, pos)) {
      DLOG(INFO) << "Click outside selection";
      return;
    }

    ThumbnailBuffer* buffer = thumbnailBuffer_.current();
    if (!buffer || buffer->hasFilled(block::Block(pos, pos + PRELOAD))) {
      triggerTime_ = -1;
    } else {
      triggerTime_ = pos;
      if (buffer)
        buffer->setPosition(pos);
      return;
    }
  }

  (*listeners())(pos);
}

void Model::zoom(RealTime time, double k) {
  ZoomProto z(widget::waveform::zoom(zoomLocker_.get(), realLength(), time, k));
  persist::set<ZoomProto>(z, file_);
}

void Model::setLoopPointList(const LoopPointList& loops) {
  timeSelection_ = audio::getTimeSelection(loops, length());
  selectionSource_->setSelection(timeSelection_);
  BlockSet::const_iterator i = timeSelection_.begin();
  for (; i != timeSelection_.end(); ++i) {
    if (time_ < i->second) {
      if (time_ < i->first)
        setTriggerTime(i->first);
      return;
    }
  }
  setTriggerTime(timeSelection_.begin()->first);
}

void Model::operator()(const VirtualFile& f) {
  if (thumbnailBuffer_.next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }
  file_ = f;
  player()->setState(audio::transport::STOPPED);

  ptr<ThumbnailBuffer> buffer(new ThumbnailBuffer(f));

  buffer->thumbnail()->addListener(&components()->waveform_);
  selectionSource_ = new Selection(new BufferSource(buffer->buffer()));
  player()->setSource(selectionSource_);
  thumbnailBuffer_.setNext(buffer.transfer());
  threads()->fetchThread()->notify();

  persist::Data<LoopPointList>* setter = persist::setter<LoopPointList>(f);
  components()->loops_.setData(setter);

  stretchLocker_.listenTo(persist::setter<Stretch>(f));
  zoomLocker_.listenTo(persist::setter<ZoomProto>(f));
  loopLocker_.listenTo(setter);

  stretchLocker_.set(persist::get<Stretch>(f));
  loopLocker_.set(persist::get<LoopPointList>(f));
  components()->songData_.setFile(f);

#ifdef TODO
  const Stretch& stretch = loop.stretch();
  static const double DELTA = 0.00001;
  double timeRatio = timeScale(stretch);
  if (!(stretch.passthrough_when_disabled() &&
        near(timeRatio, 1.0, DELTA) &&
        near(stretch::pitchScale(stretch), 1.0, DELTA))) {
    source.reset(new Stretchy(source.transfer(), stretch));
  }

  source.reset(new Stereo(source.transfer(), stretch.stereo()));
#endif
}

void Model::checkChanged() {
  fileLocker_.broadcastIfChanged(this); // TODO
  stretchLocker_.broadcastIfChanged(listeners());
  loopLocker_.broadcastIfChanged(listeners());
  zoomLocker_.broadcastIfChanged(&components()->waveform_);
}

#if 0
const block::BlockSet Model::getTimeSelection() const {
  ScopedLock l(lock_);
  return timeSelection_;
}
#endif

}  // namespace slow
}  // namespace rec
