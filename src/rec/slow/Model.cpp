#include "rec/slow/Model.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Frame.h"
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

namespace {

class LoopListenerImpl : public DataListener<LoopPointList> {
 public:
  explicit LoopListenerImpl(Model* model) : model_(model) {}
  virtual void onDataChange(const LoopPointList& p) {
    (*model_)(p);
  }

 private:
  Model* const model_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(LoopListenerImpl);
};

}

Model::Model(Instance* i) : HasInstance(i),
                            time_(0),
                            triggerPosition_(-1),
                            updateBuffer_(2, 1024),
                            loopListener_(new LoopListenerImpl(this)) {
  audio::Source *s = new FrameSource<short, 2>(thumbnailBuffer_.buffer()->frames());
  player()->setSource(s);
  player()->timeBroadcaster()->addListener(this);
  components()->waveform_.setAudioThumbnail(thumbnailBuffer_.thumbnail());
}

void Model::setFile(const VirtualFile& f) {
  // DLOG(INFO) << "setFile: " << f.ShortDebugString();
  player()->clear();
  components()->playerController_.clearLevels();
  components()->directoryTree_.refreshNode(file_);

	ScopedLock l(lock_);
  VirtualFile oldFile = file_;
  file_ = f;

  if (!thumbnailBuffer_.setReader(file_)) {
    LOG(ERROR) << "Couldn't set reader for " << getFullDisplayName(f);
    return;
  }

  bool isEmpty = empty();
  components()->waveform_.setEmpty(isEmpty);

  if (isEmpty) {
    DLOG(INFO) << "Setting empty file";
  } else {
    components()->directoryTree_.refreshNode(file_);

    LoopPointList loop = persist::get<LoopPointList>(f);
    if (!loop.loop_point_size()) {
      loop.add_loop_point()->set_selected(true);
      RealTime time = thumbnailBuffer_.buffer()->length();
      loop.add_loop_point()->set_time(time);
    }

    persist::set(loop, f);
    threads()->fillThread()->notify();
  }

  persist::setGlobal(f);
}

thread::Result Model::fillOnce() {
  {
    ScopedLock l(lock_);
    FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
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
      jumpToTime(triggerPosition_);

    int64 pos = buffer->position();
    int64 filled = buffer->fillNextBlock();

    if (!thumbnailBuffer_.cacheWritten()) {
      AudioSourceChannelInfo info;
      info.numSamples = filled;
      info.buffer = &updateBuffer_;
      info.startSample = 0;
      updateBuffer_.setSize(2, filled, false, false, true);
      FrameSource<short, 2> src(buffer->frames());
      src.setNextReadPosition(pos);
      src.getNextAudioBlock(info);
      thumbnailBuffer_.addBlock(pos, info);
    }
  }

  thread::callAsync(&components()->waveform_, &Waveform::repaint);
  return thread::YIELD;
}

void Model::zoom(RealTime time, double k) {
  ZoomProto z(widget::waveform::zoom(persist::get<ZoomProto>(file_),
                                     player()->realLength(), time, k));
  persist::set(z, file_);
}

void Model::jumpToTime(SamplePosition pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection_, pos)) {
      DLOG(INFO) << "Tried to jump to position outside selection " << pos;
      return;
    }

    FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
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

void Model::operator()(const LoopPointList& loops) {
  if (empty())
    return;

  // DLOG(INFO) << loops.ShortDebugString();
  timeSelection_ = audio::getTimeSelection(loops);
  if (timeSelection_.empty()) {
    DLOG(ERROR) << "Empty selection";
  } else {
    BlockSet::const_iterator i = timeSelection_.begin();
    for (; i != timeSelection_.end(); ++i) {
      if (time_ < i->second) {
        if (time_ < i->first)
          jumpToTime(i->first);
        return;
      }
    }
    jumpToTime(timeSelection_.begin()->first);
  }
}

void Model::setCursorTime(int index, RealTime time) {
  if (index < 0) {
    jumpToTime(audio::timeToSamples(time));
  } else {
  	VirtualFile f = file();
    LoopPointList loops(persist::get<LoopPointList>(f));
    loops.mutable_loop_point(index)->set_time(time);
    persist::set(loops, f);
  }
}

}  // namespace slow
}  // namespace rec
