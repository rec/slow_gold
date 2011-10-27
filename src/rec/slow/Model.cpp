#include "rec/slow/Model.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Frame.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/data/Data.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/Threads.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

#include "rec/slow/CurrentTime.h"
#include "rec/slow/CurrentFile.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;
using namespace rec::gui::audio;
using namespace rec::music;
using namespace rec::util::block;
using namespace rec::widget::waveform;

const int PARAMETER_WAIT = 1000;
const int PRELOAD = 10000;

Model::Model(Instance* i) : HasInstance(i),
                            updateBuffer_(2, 1024),
                            updateSource_(thumbnailBuffer_.buffer()->frames()) {
  audio::Source *s = new FrameSource<short, 2>(thumbnailBuffer_.buffer()->frames());
  player()->setSource(s);
  player()->timeBroadcaster()->addListener(currentTime());
  components()->waveform_.setAudioThumbnail(thumbnailBuffer_.thumbnail());
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}

Model::~Model() {}

thread::Result Model::fillOnce() {
  FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
  if (buffer && buffer->isFull()) {
    thumbnailBuffer_.writeThumbnail();
    return static_cast<thread::Result>(PARAMETER_WAIT);
  }

  bool empty = false;
  if (currentTime()->jumpToTime() == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(currentTime()->timeSelection(), buffer->filled());
    if (!fill.empty()) {
      BlockList fillList = fillSeries(fill, time(), length());
      if (!fillList.empty())
        buffer->setNextFillPosition(fillList.begin()->first);
      else
        empty = true;

    } else {
      empty = true;
    }
  }

  if (currentTime()->jumpToTime() != -1 &&
      buffer->hasFilled(block::Block(currentTime()->jumpToTime(),
                                     currentTime()->jumpToTime() + PRELOAD))) {
    jumpToTime(currentTime()->jumpToTime());
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

void Model::jumpToTime(Samples<44100> pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(currentTime()->timeSelection(), pos)) {
      DLOG(ERROR) << "Tried to jump to position outside selection " << pos;
      return;
    }

    FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
    currentTime()->setJumpToTime(pos);
    if (buffer && !buffer->hasFilled(block::Block(pos, pos + PRELOAD))) {
      buffer->setNextFillPosition(pos);
      if (player()->state())
        return;
    }
    currentTime()->setJumpToTime(-1);
  }

	player()->setNextReadPosition(pos);
}

}  // namespace slow
}  // namespace rec
