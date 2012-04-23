#include "rec/slow/BufferFiller.h"

#include "rec/slow/CurrentTime.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::gui::audio;
using namespace rec::util::block;
using namespace rec::widget::waveform;

const int PARAMETER_WAIT = 1000;
const int PRELOAD = 10000;

BufferFiller::BufferFiller(Instance* i)
  : HasInstance(i),
    updateBuffer_(2, 1024),
    updateSource_(trackBuffer_.reader()->makeSource()) {
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}

BufferFiller::~BufferFiller() {}

bool BufferFiller::isFull() const {
  return trackBuffer_.reader().isFull();
}

void BufferFiller::fillOnce() {
  BufferedReader* reader = trackBuffer_.reader();

  bool empty = false;
  Samples<44100> jump = currentTime()->jumpTime();

  if (jump == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(currentTime()->timeSelection(), reader->filled());
    // block::print(DLOG(INFO), fill);
    if (!fill.empty()) {
      BlockList fillList = fillSeries(fill, time(), length());
      if (!fillList.empty())
        reader->setNextFillPosition(fillList.begin()->first);
      else
        empty = true;

    } else {
      empty = true;
    }
  }

  if (jump != -1 && reader->hasFilled(block::Block(jump, jump + PRELOAD)))
    currentTime()->jumpToTime(jump);

  int64 pos = reader->position();
  int filled = static_cast<int>(reader->fillNextBlock());
  DCHECK(filled);

  updateInfo_.numSamples = filled;
  updateBuffer_.setSize(2, filled, false, false, true);
  updateSource_->setNextReadPosition(pos);
  updateSource_->getNextAudioBlock(updateInfo_);
  trackBuffer_.addBlock(pos, updateInfo_);

  thread::callAsync(components()->waveform_.get(),
                    &Waveform::repaintBlock,
                    block::makeBlock(pos, pos + filled));

  if (isFull())
    trackBuffer_.writeThumbnail();
}

}  // namespace slow
}  // namespace rec

