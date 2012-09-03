#include "rec/slow/FillerThread.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/util/range/Difference.h"
#include "rec/util/range/WrapSeries.h"
#include "rec/util/range/Range.h"
#include "rec/util/range/SampleRange.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
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
    SampleRangeVector sel = currentTime()->timeSelection();
    SampleRangeVector readerFilled = reader->filled();
    SampleRangeVector fill = difference<SampleTime>(sel, readerFilled);
    if (!fill.empty()) {
      SampleTime time = currentTime()->time();
      SampleRangeVector fillList = getUnfilledBlocks(fill, time, length(), STOP_AT_END);
      if (!fillList.empty())
        reader->setNextFillPosition(fillList.begin()->begin_);
      else
        LOG(ERROR) << "No fill list";
    }
  }
}

void FillerThread::run() {
  setFillPositionOrJump();
  while (true) {
    SampleRange b = bufferFiller()->fillOnce();
    if (threadShouldExit() || b.empty())
      return;
    setFillPositionOrJump();
    {
      MessageManagerLock l(this);
      if (l.lockWasGained())
        components()->waveform_->repaintRange(b);
    }
    wait(FILLER_THREAD_WAIT);
  }
}

}  // namespace slow
}  // namespace rec
