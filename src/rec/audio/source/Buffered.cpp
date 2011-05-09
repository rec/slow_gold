#include "rec/audio/source/Buffered.h"
#include "rec/audio/util/CopySamples.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Buffered::Buffered(Source* source, SampleTime size)
    : source_(source),
      buffer_(2, size),
      circular_(size),
      notifyThread_(NULL),
      nextEnd_(0) {
  setBuffer(&buffer_);
}

void Buffered::getNextAudioBlock(const Info& i) {
  {
    ScopedLock l(lock_);
    circular_.consume(i.numSamples);
  }

  BufferSource::getNextAudioBlock(i);
  notify();
}

bool Buffered::fillBuffer(SampleTime size) {
  ptr<Source> trash;
  Range<SampleTime> fillable;
  {
    ScopedLock l(lock_);
    if (nextSource_) {
      nextSource_.swap(source_);
      nextSource_.swap(trash);

      SampleTime e = nextEnd_;
      if (e > circular_.size())
        e -= circular_.size();

      circular_.end_ = (e < circular_.begin_) ? circular_.begin_ : nextEnd_;
    }

    fillable = circular_.fillable();
  }

  Info info;
  info.buffer = &buffer_;
  info.startSample = fillable.begin_;
  info.numSamples = juce::jmin(size, fillable.size());

  if (info.numSamples <= 0) {
    DCHECK_EQ(info.numSamples, 0);
    return false;
  }
  source_->getNextAudioBlock(info);

  ScopedLock l(lock_);
  circular_.fill(size);
  return true;
}

void Buffered::setSource(Source* source, SampleTime offset) {
  ptr<Source> src(source);
  {
    ScopedLock l(lock_);
    nextSource_.swap(src);
    nextEnd_ = circular_.begin_ + offset;
  }
  DCHECK(!src.get());
}

}  // namespace source
}  // namespace audio
}  // namespace rec

