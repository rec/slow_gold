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
  const static int MINIMUM_FILL_SIZE = 4096;

  DoubleStretchy(const Description& description, Source* s0, Source* s1)
      : position_(0),
        currentReader_(0),
        descriptionChanged_(false),
        description_(description),
        gettingBlock_(false) {
    readers_[0].source_.reset(s0);
    readers_[1].source_.reset(s1);

    readers_[0].reset(description, 0);
  }

  void setDescription(const Description& description) {
    ScopedLock l(lock_);
    descriptionChanged_ = true;
    description_.CopyFrom(description);
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
      if (i->buffered_)
        i->buffered_->setNextReadPosition(position + i->offset_);
    }
  }

  virtual int available() const {
    ScopedLock l(lock_);
    return source()->available();
  }

  virtual void prepareToPlay(int s, double r) {
    for (SourceReader* i = readers_; i != readers_ + SIZE; ++i) {
      if (i->buffered_)
        i->buffered_->prepareToPlay(s, r);
    }
  }

  virtual void releaseResources() {
    for (SourceReader* i = readers_; i != readers_ + SIZE; ++i) {
      if (i->buffered_)
        i->buffered_->releaseResources();
    }
  }

  virtual bool fillNext() {
    // Make sure our memory management is done out of the lock.
    scoped_ptr<Buffered> bufferDeleter;
    scoped_ptr< Stretchy<Source> > stretchyDeleter;

    {
      ScopedLock l(lock_);

      int prefillSize = description_.prefill_size();
      bool isNext = next() && source()->ready(prefillSize);
      Buffered* fill = isNext ? next() : source();
      int chunkSize = description_.chunk_size();

      bool result;
      {
        ScopedUnlock l(lock_);
        result = fill->fillNext(chunkSize);
      }

      if (gettingBlock_)
        return true;  // Don't rock the boat until that's done.

      if (isNext) {
        if (fill->ready(prefillSize)) {
          // Your new file is ready!
          SourceReader& current = readers_[currentReader_];
          current.buffered_.swap(bufferDeleter);
          current.reader_.swap(stretchyDeleter);
          currentReader_ = 1 - currentReader_;
          DCHECK(!next());
        }

      } else if (descriptionChanged_) {
        descriptionChanged_ = false;

        SourceReader& sr = readers_[currentReader_];
        float scale = description_.time_scale() / sr.description_.time_scale();
        int offset = (position_ + sr.offset_) * scale - position_;
        readers_[1 - currentReader_].reset(description_, offset);
      }

      return result || next();
    }
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    ScopedLock l(lock_);
    Buffered* buffered = source();

    gettingBlock_ = true;
    {
      ScopedUnlock l(lock_);
      buffered->getNextAudioBlock(info);
    }
    gettingBlock_ = false;
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
    scoped_ptr<Source> source_;
    Description description_;
    int offset_;

    scoped_ptr< Stretchy<Source> > reader_;
    scoped_ptr<Buffered> buffered_;

    void reset(const Description& description, int offset) {
      description_.CopyFrom(description);
      reader_.reset(new Stretchy<Source>(description_, source_.get()));
      buffered_.reset(new Buffered(description_.channels(), reader_.get()));
      offset_ = offset;
    }
  };

  Buffered* source() {
    return readers_[currentReader_].buffered_.get();
  }

  const Buffered* source() const {
    return readers_[currentReader_].buffered_.get();
  }

  Buffered* next() {
    return readers_[1 - currentReader_].buffered_.get();
  }

  static const int SIZE = 2;
  SourceReader readers_[SIZE];
  int currentReader_;
  bool descriptionChanged_;
  Description description_;

  int position_;
  CriticalSection lock_;
  int gettingBlock_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchy);
};


template <typename Source>
class DoubleStretchyThread : public DoubleStretchy<Source>, Thread {
 public:
  typedef rec::audio::timescaler::Description Description;

  DoubleStretchyThread(const Description& d, Source* s0, Source* s1)
      : DoubleStretchy<Source>(d, s0, s1),
        Thread("DoubleStretchy"),
        waitTime_(d.inactive_wait_time()) {
    setPriority(d.thread_priority());
    startThread();
  }

  void run() {
    while (!threadShouldExit()) {
      if (!(this->fillNext() || threadShouldExit()))
        wait(waitTime_);
    }
  }

  void stop() {
    signalThreadShouldExit();
    notify();
  }

 private:
  int waitTime_;
  DISALLOW_COPY_AND_ASSIGN(DoubleStretchyThread);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
