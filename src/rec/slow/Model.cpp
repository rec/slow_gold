#include "rec/slow/Model.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Frame.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/data/Data.h"
#include "rec/music/CreateMusicFileReader.h"
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
    model_->setLoopPointList(p);
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
                            updateSource_(thumbnailBuffer_.buffer()->frames()),
                            loopListener_(new LoopListenerImpl(this)) {
  audio::Source *s = new FrameSource<short, 2>(thumbnailBuffer_.buffer()->frames());
  player()->setSource(s);
  player()->timeBroadcaster()->addListener(this);
  components()->waveform_.setAudioThumbnail(thumbnailBuffer_.thumbnail());
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}

void Model::setFile(const VirtualFile& f) {
  player()->clear();
  components()->playerController_.clearLevels();
  components()->directoryTree_.refreshNode(file_);

  bool isEmpty = file::empty(f);
  components()->waveform_.setEmpty(isEmpty);

  {
    ScopedLock l(lock_);
    file_ = f;
  }
  components()->directoryTree_.refreshNode(f);
  data::set(f);

  if (isEmpty)
    return;

  if (!thumbnailBuffer_.setReader(f, music::createMusicFileReader(f))) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  LoopPointList loopPointList = data::get<LoopPointList>(f);
  if (!loopPointList.loop_point_size()) {
    loopPointList.add_loop_point()->set_selected(true);
    RealTime time = Samples<44100>(thumbnailBuffer_.buffer()->length());
    loopPointList.add_loop_point()->set_time(time);
  }
  data::set(loopPointList, f);

  threads()->fillThread()->notify();
}

thread::Result Model::fillOnce() {
  {
    FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
    if (buffer && buffer->isFull()) {
      thumbnailBuffer_.writeThumbnail();
      return static_cast<thread::Result>(PARAMETER_WAIT);
    }

    bool empty = false;
    if (triggerPosition_ == -1) {
      // Find the first moment in the selection after "time" that needs to be filled.
      BlockSet fill = difference(timeSelection_, buffer->filled());
      if (!fill.empty()) {
        BlockList fillList = fillSeries(fill, time_, player()->length());
        if (!fillList.empty())
          buffer->setNextFillPosition(fillList.begin()->first);
        else
          empty = true;

      } else {
        empty = true;
      }
    }

    if (triggerPosition_ != -1 &&
        buffer->hasFilled(block::Block(triggerPosition_,
                                       triggerPosition_ + PRELOAD))) {
      jumpToTime(triggerPosition_);
    }

    int64 pos = buffer->position();
    int filled = static_cast<int>(buffer->fillNextBlock());
    DCHECK(filled);

    updateInfo_.numSamples = filled;
    updateBuffer_.setSize(2, filled, false, false, true);
    updateSource_.setNextReadPosition(pos);
    updateSource_.getNextAudioBlock(updateInfo_);
    thumbnailBuffer_.addBlock(pos, updateInfo_);
  }

  thread::callAsync(&components()->waveform_, &Waveform::repaint);
  return thread::YIELD;
}

void Model::zoom(RealTime time, double k) {
  ZoomProto z(widget::waveform::zoom(data::get<ZoomProto>(file_),
                                     player()->length(), time, k));
  data::set(z, file_);
}

void Model::jumpToTime(Samples<44100> pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection_, pos)) {
      // TODO: fix this.
      LOG(ERROR) << "Tried to jump to position outside selection " << pos;
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

void Model::setLoopPointList(const LoopPointList& loops) {
  if (empty())
    return;

  timeSelection_ = audio::getTimeSelection(loops);
  if (timeSelection_.empty()) {
    // TODO: fix this.
    LOG(ERROR) << "Empty selection for loops: "  << loops.ShortDebugString();
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
    jumpToTime(time);
  } else {
  	VirtualFile f = file();
    LoopPointList loops(data::get<LoopPointList>(f));
    loops.mutable_loop_point(index)->set_time(time);
    data::set(loops, f);
  }
}

}  // namespace slow
}  // namespace rec
