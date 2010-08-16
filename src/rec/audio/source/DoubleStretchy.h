#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHY__

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/stretch/description.pb.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
class DoubleStretchy : public PositionableAudioSource {
 public:
  typedef rec::audio::timescaler::Description Description;
  typedef Buffery< Stretchy<Source> > Buffered;

  DoubleStretchy(const Description& description, Source* s0, Source* s1)
      : position_(0), currentReader_(0), chunkSize_(description.chunk_size()) {
    readers_[0].source_ = s0;
    readers_[1].source_ = s1;

    readers_[0].reset(description, 0);
  }

  virtual int getTotalLength() const {
    ScopedLock l(lock_);
    return source()->getTotalLength();
  }

  virtual int getNextReadPosition() const {
    ScopedLock l(lock_);
    return source()->getNextReadPosition();
  }

  virtual void setNextReadPosition(int position) {
    ScopedLock l(lock_);
    for (SourceReader* i = readers_; i != readers_ + SIZE; ++i) {
      if (position_ <= getTotalLength())
        i->offset_ = 0;
      i->buffered_->setNextReadPosition(position - i->offset_);
    }
  }

  virtual void prepareToPlay(int s, double r) {
    for (SourceReader* i = readers_; i != readers_ + SIZE; ++i)
      i->buffered_->prepareToPlay(s, r);
  }

  virtual void releaseResources() {
    for (SourceReader* i = readers_; i != readers_ + SIZE; ++i)
      i->buffered_->releaseResources();
  }

  int available() const { return source()->available(); }

  virtual bool fillNext() {
    Buffered* buffered;
    {
      ScopedLock l(lock_);
      buffered = next();
      if (!buffered)
        buffered = source();
    }

    return buffered->fillNext(chunkSize_);
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    {
      ScopedLock l(lock_);

      if (next() && next()->available() >= info.numSamples) {
        // Your new file is ready!
        SourceReader& current = readers_[currentReader_];
        current.buffered_.reset();
        current.reader_.reset();
        currentReader_ = 1 - currentReader_;
      }
    }

    source()->getNextAudioBlock(info);
  }

  virtual bool isLooping() const {
    ScopedLock l(lock_);
    return source()->isLooping();
  }

  virtual void setLooping(bool looping) {
    ScopedLock l(lock_);
    for (SourceReader* i = readers_; i != readers_ + SIZE; ++i)
      i->buffered_->setLooping(looping);
  }

 private:
  struct SourceReader {
    Source* source_;
    Description description_;
    int offset_;

    scoped_ptr< Stretchy<Source> > reader_;
    scoped_ptr<Buffered> buffered_;

    void reset(const Description& description, int offset) {
      description_.CopyFrom(description);
      reader_.reset(new Stretchy<Source>(description_, source_));
      buffered_.reset(new Buffered(description_.channels(), reader_.get()));
      offset_ = offset;
    }
  };
  Buffered* source() { return readers_[currentReader_].buffered_.get(); }
  Buffered* next() { return readers_[1 - currentReader_].buffered_.get(); }
  const Buffered* source() const { return readers_[currentReader_].buffered_.get(); }
  const Buffered* next() const { return readers_[1 - currentReader_].buffered_.get(); }

  static const int SIZE = 2;
  SourceReader readers_[SIZE];
  int currentReader_;
  int chunkSize_;

  int position_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
