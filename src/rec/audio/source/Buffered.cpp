#include "rec/audio/source/Buffered.h"
#include "rec/audio/util/CopySamples.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Buffered::Buffered(Source* source, SamplePosition size)
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
#if 0
  DLOG(INFO) << " <- circular: " << circular_.toFill();
#endif
  notify();
}

bool Buffered::fillBuffer(SamplePosition size) {
  ptr<Source> trash;
  Range<SamplePosition> fillable;
  DLOG(INFO) << "here!";
  {
    ScopedLock l(lock_);
    if (nextSource_) {
      //      DLOG(INFO) << "new source";
      nextSource_.swap(source_);
      nextSource_.swap(trash);

      SamplePosition e = nextEnd_;
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
    DLOG(INFO) << "out! " << fillable.begin_ << ", " << fillable.end_
               << " circ! " << circular_.begin_ << ", " << circular_.end_;
    return false;
  }
  source_->getNextAudioBlock(info);

  ScopedLock l(lock_);
  circular_.fill(size);
#if 0
  DLOG(INFO) << " -> circular: " << circular_.toFill()
             << " startSample: " << info.startSample
             << " numSamples: " << info.numSamples;

             #endif
  return true;
}

#if 0
  oid setSource(Source* source, SamplePosition offset);

void Buffered::setSource(Source* source, SamplePosition offset) {
  ptr<Source> src(source);
  {
    ScopedLock l(lock_);
    nextSource_.swap(src);
    nextEnd_ = circular_.begin_ + offset;
  }
  DCHECK(!src.get());
}
#endif

}  // namespace source
}  // namespace audio
}  // namespace rec

