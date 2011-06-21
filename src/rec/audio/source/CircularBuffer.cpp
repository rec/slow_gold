#if 0
#include "rec/audio/source/CircularBuffer.h"
#include "rec/audio/util/CopySamples.h"

namespace rec {
namespace audio {
namespace source {

SamplePosition CircularBuffer::fillFrom(const BufferTime& from) {
  SamplePosition num = std::min(filled_.toFill(), from.numSamples);

  Info to;
  to.buffer = &buffer_;
  to.startSample = filled_.end_;
  to.numSamples = num;

  SamplePosition wraps = to.startSample + to.numSamples - filled_.capacity_;
  if (wraps <= 0)
    return copySamples(from, to);

  Info f(from);
  to.numSamples = to.numSamples - wraps;
  DCHECK_EQ(copySamples(f, to), to.numSamples);

  to.numSamples = wraps;
  to.startSample = 0;
  f.startSample += to.numSamples;
  DCHECK_EQ(copySamples(f, to), to.numSamples);

  return num;
}


SamplePosition CircularBuffer::fillOrConsume(const BufferTime& other,
                                             SamplePosition numSamples, bool isFill) {
  if (SamplePosition wraps = std::max(filled_.end_ - filled_.capacity_, 0))


  BufferTime otherBt(other);
  BufferTime thisBt(&buffer_, isFill ? filled_.begin_ : filled_.end_);
  const BufferTime& from = isFill ? thisBt : otherBt;
  const BufferTime& to = !isFill ? thisBt : otherBt;

  SamplePosition available = isFill ? filled_.toFill() : filled_.size();
  SamplePosition num = std::min(available, blockSize);
  copy(from, to, num - wraps);
  if (wraps) {
    this
  }

  if (wraps <= 0) {
    copy(from, to, numSamples);
  } else {
    copy(from, to
  }

  BufferTime bt(other);
  to.numSamples = to.numSamples - wraps;
  DCHECK_EQ(copySamples(f, to), to.numSamples);

  to.numSamples = wraps;
  to.startSample = 0;
  f.startSample += to.numSamples;
  DCHECK_EQ(copySamples(f, to), to.numSamples);

  return num;
}

SamplePosition CircularBuffer::consumeTo(const Info& to) {
  SamplePosition num = std::min(filled_.toConsume(), from.numSamples);

  Info from;
  from.buffer = &buffer_;
  from.startSample = filled_.begin_;
  from.numSamples = num;

  SamplePosition wraps = from.startSample + to.numSamples - filled_.capacity_;
  if (wraps <= 0)
    return copySamples(from, to);

  Info f(from);
  to.numSamples = to.numSamples - wraps;
  DCHECK_EQ(copySamples(f, to), to.numSamples);

  to.numSamples = wraps;
  to.startSample = 0;
  f.startSample += to.numSamples;
  DCHECK_EQ(copySamples(f, to), to.numSamples);

  return num;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif
