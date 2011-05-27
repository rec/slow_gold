#include "rec/slow/Model.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/GenericBufferSource.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/data/persist/Data.h"
#include "rec/util/LoopPoint.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Threads.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;
using namespace rec::gui::audio;
using namespace rec::music;
using namespace rec::util::block;
using namespace rec::widget::waveform;

static const int PARAMETER_WAIT = 1000;
static const int PRELOAD = 10000;

Model::Model(Instance* i) : HasInstance(i),
                            fileLocker_(&lock_),
                            loopLocker_(&lock_),
                            metadataLocker_(&lock_),
                            stereoLocker_(&lock_),
                            stretchLocker_(&lock_),
                            zoomLocker_(&lock_),
                            time_(0),
                            triggerTime_(-1),
                            loopData_(NULL) {
  persist::setter<VirtualFile>()->addListener(&fileLocker_);
  player()->timeBroadcaster()->addListener(this);
}

void Model::fillOnce() {
  thumbnailBuffer_.switchIfNext();
  ThumbnailBuffer* buffer = thumbnailBuffer_.current();
  if (!buffer || buffer->isFull()) {
    if (buffer)
      buffer->writeThumbnail();

    Thread::getCurrentThread()->wait(PARAMETER_WAIT);
    return;
  }

  if (triggerTime_ == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(timeSelection_, buffer->filled());
    BlockList fillList = fillSeries(fill, time_, player()->length());
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
    if (!buffer) {
      triggerTime_ = -1;
      return;
    }
    triggerTime_ = pos;
    if (!buffer->hasFilled(block::Block(pos, pos + PRELOAD))) {
      buffer->setPosition(pos);
      return;
    }
    triggerTime_ = -1;
  }

  (*listeners())(pos);
}

void Model::zoom(RealTime time, double k) {
  ZoomProto z(widget::waveform::zoom(zoomLocker_.get(), player()->realLength(), time, k));
  persist::set<ZoomProto>(z, file_);
}

void Model::operator()(const LoopPointList& loops) {
  timeSelection_ = audio::getTimeSelection(loops, player()->length());
  player()->setSelection(timeSelection_);
  BlockSet::const_iterator i = timeSelection_.begin();
  components()->waveform_(loops);
  for (; i != timeSelection_.end(); ++i) {
    if (time_ < i->second) {
      if (time_ < i->first)
        setTriggerTime(i->first);
      return;
    }
  }
  setTriggerTime(timeSelection_.begin()->first);
}

namespace {

template <typename Proto>
persist::Data<Proto>* updateLocker(thread::Locker<Proto>* locker, const VirtualFile& file) {
  persist::Data<Proto>* s = persist::setter<Proto>(file);
  locker->listenTo(s);
  locker->set(s->get());
  return s;
}

}  // namespace

void Model::operator()(const VirtualFile& f) {
  if (thumbnailBuffer_.next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }
  components()->directoryTree_.refreshNode(file_);
  file_ = f;
  player()->setState(audio::transport::STOPPED);
  player()->timeBroadcaster()->broadcast(0);
  player()->clearSource();

  loopData_ = updateLocker(&loopLocker_, f);
  components()->loops_.setData(loopData_);
  components()->stretchyController_.setData(updateLocker(&stereoLocker_, f));
  components()->stretchyController_.setData(updateLocker(&stretchLocker_, f));
  components()->songData_.setData(updateLocker(&metadataLocker_, f));
  updateLocker(&zoomLocker_, f);

  if (empty())
    return;

  LoopPointList loop = loopData_->get();
  if (!loop.loop_point_size()) {
    loop.add_loop_point()->set_selected(true);
    data::set(loopData_, loop);
    loopLocker_.set(loop);
  }

  ptr<ThumbnailBuffer> buffer(new ThumbnailBuffer(f));
  if (!buffer->thumbnail()) {
    LOG(ERROR) << "File " << f.DebugString() << " doesn't exist";
    return;
  }

  buffer->thumbnail()->addListener(&components()->waveform_);
  player()->setSource(new GenericBufferSource<short, 2>(*buffer));
  player()->setStretch(stretchLocker_.get());
  thumbnailBuffer_.setNext(buffer.transfer());
  threads()->fetchThread()->notify();
  player()->setNextReadPosition(0);
  (*components()->transportController_.levelListener())(vector<double>());
}


void Model::checkChanged() {
  fileLocker_.broadcastIfChanged(this); // TODO

  stretchLocker_.broadcastIfChanged(listeners());
  loopLocker_.broadcastIfChanged(this);
  stereoLocker_.broadcastIfChanged(listeners());
  // metadataLocker_.broadcastIfChanged(&components()->songData_);
  zoomLocker_.broadcastIfChanged(&components()->waveform_);
}

void Model::toggleSelectionSegment(RealTime time) {
  ScopedLock l(lock_);
  LoopPointList loops(loopLocker_.get());

  int i = 0, size = loops.loop_point_size();
  for (; i < size && loops.loop_point(i).time() <= time; ++i);
  LoopPoint* lp = loops.mutable_loop_point(i - 1);
  lp->set_selected(!lp->selected());
  persist::set(loops, file_);
}

void Model::setCursorTime(int index, RealTime time) {
  if (index < 0) {
    setTriggerTime(audio::timeToSamples(time));
  } else {
    LoopPointList loops = loopLocker_.get();
    loops.mutable_loop_point(index)->set_time(time);

    data::set(loopData_, loops);
  }
}

}  // namespace slow
}  // namespace rec
