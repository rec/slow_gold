#include "rec/slow/FillerThread.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/audio/source/Selection.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Components.h"
#include "rec/util/block/Block.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::util::block;
using namespace rec::widget::waveform;

static const int FILLER_THREAD_WAIT = 5;

void FillerThread::setFillPositionOrJump() {
  SampleTime jump = currentTime()->requestedTime();
  BufferedReader* reader = bufferFiller()->reader();
  if (jump >= 0) {
    if (reader->coversTime(jump))
      currentTime()->jumpToTime(jump);
  } else {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet sel = convertToBlockSet<SampleTime>(currentTime()->timeSelection());
    BlockSet readerFilled = convertToBlockSet<SampleTime>(reader->filled());
    BlockSet fill = difference(sel, readerFilled);
    if (!fill.empty()) {
      BlockList fillList = fillSeries(fill, currentTime()->time(), length());
      if (!fillList.empty())
        reader->setNextFillPosition(fillList.begin()->first);
      else
        LOG(ERROR) << "No fill list";
    }
  }
}

void FillerThread::run() {
  setFillPositionOrJump();
  while (true) {
    Block b = bufferFiller()->fillOnce();
    if (threadShouldExit() || block::empty(b))
      return;
    setFillPositionOrJump();
    {
      MessageManagerLock l(this);
      if (l.lockWasGained())
        components()->waveform_->repaintBlock(b);
    }
    wait(FILLER_THREAD_WAIT);
  }
}

}  // namespace slow
}  // namespace rec
