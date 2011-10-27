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
#include "rec/slow/Threads.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

#include "rec/slow/methods/TimeMethods.h"
#include "rec/slow/CurrentFile.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;
using namespace rec::gui::audio;
using namespace rec::music;
using namespace rec::util::block;
using namespace rec::widget::waveform;

using methods::TimeMethods;

const int PARAMETER_WAIT = 1000;
const int PRELOAD = 10000;

Model::Model(Instance* i) : HasInstance(i),
                            time_(0),
                            triggerPosition_(-1),
                            updateBuffer_(2, 1024),
                            updateSource_(thumbnailBuffer_.buffer()->frames()) {
  audio::Source *s = new FrameSource<short, 2>(thumbnailBuffer_.buffer()->frames());
  player()->setSource(s);
  player()->timeBroadcaster()->addListener(this);
  components()->waveform_.setAudioThumbnail(thumbnailBuffer_.thumbnail());
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}

Model::~Model() {}

void Model::clear() {
  time_ = triggerPosition_ = 0;
  timeSelection_.clear();
}

thread::Result Model::fillOnce() {
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

  thread::callAsync(&components()->waveform_, &Waveform::repaint);
  return thread::YIELD;
}

void Model::zoom(RealTime time, double k) {
  widget::waveform::zoom(file(), player()->length(), time, k);
}

void Model::jumpToTime(Samples<44100> pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection_, pos)) {
      DLOG(ERROR) << "Tried to jump to position outside selection " << pos;
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

	player()->setNextReadPosition(pos);
}

void Model::onDataChange(const LoopPointList& loops) {
  if (!empty()) {
    timeSelection_ = audio::getTimeSelection(loops, player()->length());
    TimeMethods(instance_).jumpToTimeSelection(timeSelection_, time_);
  } else {
    LOG(ERROR) << "Setting empty loop point list";
  }
}

void Model::setCursorTime(int index, RealTime time) {
  TimeMethods(instance_).setCursorTime(index, time);
}

}  // namespace slow
}  // namespace rec
