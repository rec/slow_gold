#include "rec/slow/Model.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/data/persist/Data.h"
#include "rec/data/persist/Persist.h"
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
                            gainLocker_(&lock_),
                            loopLocker_(&lock_),
                            metadataLocker_(&lock_),
                            modeLocker_(&lock_),
                            stereoLocker_(&lock_),
                            stretchLocker_(&lock_),
                            zoomLocker_(&lock_),
                            time_(0),
                            triggerPosition_(-1),
                            loopData_(NULL),
                            updateBuffer_(2, 1024) {
  persist::setter<VirtualFile>()->addListener(&fileLocker_);
  player()->timeBroadcaster()->addListener(this);
}

thread::Result Model::fillOnce() {
  ScopedLock l(lock_);
  ThumbnailFillableBuffer* buffer = thumbnailBuffer_.buffer();
  if (buffer && buffer->isFull()) {
    thumbnailBuffer_.writeThumbnail();
    return static_cast<thread::Result>(PARAMETER_WAIT);
  }

  if (triggerPosition_ == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(timeSelection_, buffer->filled());
    BlockList fillList = fillSeries(fill, time_, player()->length());
    if (!fillList.empty())
      buffer->setNextFillPosition(fillList.begin()->first);
  }

  if (triggerPosition_ != -1)
    jumpToSamplePosition(triggerPosition_);

  int64 pos = buffer->position();
  int64 filled = buffer->fillNextBlock();

  if (CachedThumbnail* th = thumbnailBuffer_.thumbnail()) {
    components()->waveform_(th->thumbnail());
    if (!th->cacheWritten()) {
      AudioSourceChannelInfo info;
      info.numSamples = filled;
      info.buffer = &updateBuffer_;
      info.startSample = 0;
      updateBuffer_.setSize(2, filled, false, false, true);
      FrameSource<short, 2> src(thumbnailBuffer_.buffer()->frames());
      src.setNextReadPosition(pos);
      src.getNextAudioBlock(info);
      (*thumbnailBuffer_.thumbnail())(info);
    }
  }

  return thread::YIELD;
}

void Model::jumpToTime(RealTime t) {
  jumpToSamplePosition(audio::timeToSamples(t));
}

void Model::jumpToSamplePosition(SamplePosition pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection_, pos)) {
      DLOG(INFO) << "Tried to jump to position outside selection " << pos;
      return;
    }

    ThumbnailFillableBuffer* buffer = thumbnailBuffer_.buffer();
    triggerPosition_ = pos;
    if (buffer && !buffer->hasFilled(block::Block(pos, pos + PRELOAD))) {
      buffer->setNextFillPosition(pos);
      if (player()->state())
        return;
    }
    triggerPosition_ = -1;
  }

  (*listeners())(pos);
}

void Model::zoom(RealTime time, double k) {
  ZoomProto z(widget::waveform::zoom(zoomLocker_.get(), player()->realLength(), time, k));
  persist::set<ZoomProto>(z, file_);
}

void Model::operator()(const LoopPointList& loops) {
  components()->waveform_(loops);
  components()->loops_(loops);

  timeSelection_ = audio::getTimeSelection(loops, player()->length());
  player()->setSelection(timeSelection_);
  if (timeSelection_.empty()) {
    DLOG(ERROR) << "Empty selection";
  } else {
    BlockSet::const_iterator i = timeSelection_.begin();
    for (; i != timeSelection_.end(); ++i) {
      if (time_ < i->second) {
        if (time_ < i->first)
          jumpToSamplePosition(i->first);
        return;
      }
    }
    jumpToSamplePosition(timeSelection_.begin()->first);
  }
}

namespace {

template <typename Proto>
persist::Data<Proto>* updateLocker(thread::Locker<Proto>* locker,
                                   const VirtualFile& file) {
  persist::Data<Proto>* s = persist::setter<Proto>(file);
  locker->listenTo(s);
  locker->set(s->get());
  return s;
}

}  // namespace

void Model::operator()(const VirtualFile& f) {
  player()->setState(audio::transport::STOPPED);
  player()->timeBroadcaster()->broadcast(0);
  player()->clearSource();

  ScopedLock l(lock_);
  {
    Waveform* waveform = &components()->waveform_;
    ScopedLock l(*waveform->lock());
    if (!thumbnailBuffer_.setReader(f)) {
      LOG(ERROR) << "Couldn't set reader for "
                 << getFullDisplayName(f);
      waveform->setAudioThumbnail(NULL);
      return;
    }
    waveform->setAudioThumbnail(thumbnailBuffer_.thumbnail()->thumbnail());
  }
  components()->directoryTree_.refreshNode(file_);
  file_ = f;

  loopData_ = updateLocker(&loopLocker_, f);
  components()->loops_.setData(loopData_);
  player()->setData(updateLocker(&gainLocker_, f));
  components()->playerController_.modeSelector()->setData(updateLocker(&modeLocker_, f));
  components()->playerController_.setData(updateLocker(&stereoLocker_, f));
  components()->playerController_.setData(updateLocker(&stretchLocker_, f));
  components()->songData_.setData(updateLocker(&metadataLocker_, f));
  components()->playerController_.setData(persist::setter<rec::audio::Gain>(f));
  updateLocker(&zoomLocker_, f);

  if (empty())
    return;

  LoopPointList loop = loopData_->get();
  if (!loop.loop_point_size()) {
    loop.add_loop_point()->set_selected(true);
    data::set(loopData_, loop);
  }

  loopLocker_.set(loop);

#ifdef COMPACT_BUFFERS
  const audio::Frames<short, 2>& frames = thumbnailBuffer_.buffer()->frames();
  // DLOG(INFO) << &frames;
  PositionableAudioSource* s = new FrameSource<short, 2>(frames);

  player()->setSource(s, stretchLocker_.get(),
                      stereoLocker_.get(), timeSelection_);

#else
  player()->setSource(new BufferSource(*buffer->buffer()), stretchLocker_.get(),
                      stereoLocker_.get(), timeSelection_);
#endif
  // player()->setStretch(stretchLocker_.get());
  threads()->fillThread()->notify();
  player()->setNextReadPosition(0);
  (*components()->playerController_.levelListener())(LevelVector());
}


void Model::checkChanged() {
  fileLocker_.broadcastIfChanged(this); // TODO

  stretchLocker_.broadcastIfChanged(listeners());
  loopLocker_.broadcastIfChanged(this);
  stereoLocker_.broadcastIfChanged(listeners());
  gainLocker_.broadcastIfChanged(listeners());
  modeLocker_.broadcastIfChanged(listeners());
  // metadataLocker_.broadcastIfChanged(&components()->songData_);
  zoomLocker_.broadcastIfChanged(&components()->waveform_);
}

void Model::toggleSelectionSegment(RealTime time) {
  // TODO: unify with LoopsAndTime.
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
    jumpToSamplePosition(audio::timeToSamples(time));
  } else {
    LoopPointList loops = loopLocker_.get();
    loops.mutable_loop_point(index)->set_time(time);

    data::set(loopData_, loops);
  }
}

}  // namespace slow
}  // namespace rec
