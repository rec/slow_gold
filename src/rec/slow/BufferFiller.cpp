#include "rec/slow/BufferFiller.h"

#include "rec/audio/util/MakeBufferedReader.h"
#include "rec/slow/CurrentTime.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/util/file/VirtualFile.h"
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
static const char* FILENAME = "thumbnail.stream";

BufferFiller::BufferFiller()
    : reader_(makeBufferedReader<short, 2>()),
      updateBuffer_(2, 1024),
      updateSource_(reader_->makeSource()) {
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}

BufferFiller::~BufferFiller() {}

bool BufferFiller::isFull() const {
  return reader_->isFull();
}

Samples<44100> BufferFiller::setReader(const VirtualFile& f,
                                       AudioFormatReader* reader) {
  Lock l(lock_);
  DCHECK(reader);
  DCHECK(reader->lengthInSamples);
  file_ = getShadowFile(f, FILENAME);
  thumbnail_.read(file_, reader->lengthInSamples);
  return reader_->setReader(reader);
}

block::Block BufferFiller::fillOnce(CurrentTime* currentTime) {
  Samples<44100> jump = currentTime->requestedTime();

  if (jump == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(currentTime->timeSelection(), reader_->filled());
    if (!fill.empty()) {
      BlockList fillList = fillSeries(fill, currentTime->time(),
                                      currentTime->length());
      if (!fillList.empty())
        reader_->setNextFillPosition(fillList.begin()->first);
    }
  }

  if (jump != -1 && reader_->hasFilled(block::Block(jump, jump + PRELOAD)))
    currentTime->jumpToTime(jump);

  int64 pos = reader_->position();
  int filled = static_cast<int>(reader_->fillNextBlock());
  DCHECK(filled);

  updateInfo_.numSamples = filled;
  updateBuffer_.setSize(2, filled, false, false, true);
  updateSource_->setNextReadPosition(pos);
  updateSource_->getNextAudioBlock(updateInfo_);
  thumbnail_.addBlock(pos, updateInfo_);

  if (isFull())
    thumbnail_.write(file_);

  return block::makeBlock(pos, pos + filled);

#if 0
  thread::callAsync(instance_->components_->waveform_.get(),
                    &Waveform::repaintBlock,
                    block::makeBlock(pos, pos + filled));

#endif
}

}  // namespace slow
}  // namespace rec

