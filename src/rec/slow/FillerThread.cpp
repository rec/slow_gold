#include "rec/slow/FillerThread.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Instance.h"
#include "rec/util/range/Difference.h"
#include "rec/util/range/WrapSeries.h"
#include "rec/util/range/Range.h"
#include "rec/util/range/SampleRange.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::audio::util;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

namespace {
const int FILLER_THREAD_WAIT = 5;

}  // namespace

void FillerThread::setFillPositionOrJump() {
  SampleTime jump = currentTime_->requestedTime();
  BufferedReader* reader = bufferFiller_->reader();
  if (jump >= 0) {
    if (reader->coversTime(jump))
      currentTime_->jumpToTime(jump);
  } else {
    // Find the first moment in the selection after "time" that needs to be filled.
    SampleRangeVector sel = currentTime_->timeSelection();
    SampleRangeVector readerFilled = reader->filled();
    SampleRangeVector fill = difference<SampleTime>(sel, readerFilled);
    if (!fill.empty()) {
      SampleTime time = currentTime_->time();
      SampleRangeVector fillList = getUnfilledBlocks(fill, time, reader->length(),
                                                     STOP_AT_END);
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
    SampleRange b = bufferFiller_->fillOnce();
    if (threadShouldExit() || b.empty())
      return;
    setFillPositionOrJump();
    {
      MessageManagerLock l(this);
      if (l.lockWasGained())
        getInstance()->components_->waveform_->repaintRange(b);
    }
    wait(FILLER_THREAD_WAIT);
  }
}

}  // namespace slow
}  // namespace rec
