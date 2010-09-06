#ifndef __REC_AUDIO_SOURCE_DOUBLE_LOOP__
#define __REC_AUDIO_SOURCE_DOUBLE_LOOP__

#include "rec/audio/CopySamples.h"

namespace rec {
namespace audio {
namespace stretch {

class StretchHolder

class StretchingSource : public Source, public Thread {
 public:
  explicit StretchingSource(Source* source)
      : Source("Stretching Source"),
        source_(source),
        position_(0),
        offset_(0),
        length_(0),
        looping_(false),
        rescaleNeeded_(false) {
  }

  static const final WAIT_PERIOD = 100;

  void rescale() {
    Description d;
    {
      ScopedLock l(lock_);
      d.CopyFrom(nextDescription_);
    }
    Stretcher *stretch = new Stretch();
    stretch->startStretch(d, in
    ScopedLock l(lock_);
    nextStretcher_.reset());
      nextStretcher_->startStretch(
  }

  virtual void run() {
    while (!threadShouldExit()) {
      bool rescaleNeeded = false;
      Stretcher* stretcher;
      {
        ScopedLock l(lock_);
        stretcher = stretcher_;
        if (nextStretcher_) {
          stretcher = nextStretcher_;
        } else {
          rescaleNeeded = rescaleNeeded_;
          rescaleNeeded_ = false;
        }
      }

      if (rescaleNeeded)
        rescale();

      else if (!(stretcher->readNextChunk()))
        wait(WAIT_PERIOD);
    }
  }

  void setDescription(const Description& desc) {
    ScopedLock l(lock_);
    rescaleNeeded_ = true;
    nextDescription_.CopyFrom(desc);
  }

  virtual void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
    AudioSampleBuffer* buffer;
    {
      ScopedLock l(&lock_);
      if (nextStretcherReady()) {
        double oldLength = stretcher_->getBuffer()->getNumSamples();
        double newLength = nextStretcher_->getBuffer()->getNumSamples();
        position_ *= (newLength / oldLength);
        stretcher_.reset(nextStretcher_.transfer());
        notify();
      }
      buffer = stretcher_->getBuffer();
    }
    position_ = copyCircularSamples(*buffer, position_, info);
  }

  virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    if (source_)
      source_->prepareToPlay(samplesPerBlockExpected, sampleRate);
  }

  virtual void releaseResources() {
    if (source_)
      source_->releaseResources();
  }

  virtual int getTotalLength() {
    ScopedLock l(lock_);
    return length_;
  }

  virtual bool isLooping() const          { return isLooping_; }
  virtual void setLooping(bool looping)   { looping_ = looping; }
  virtual int getNextReadPosition() const { return position_; }
  virtual void setNextReadPosition(int p) { position_ = p; }
  virtual bool isLooping() const          { return isLooping_; }

  virtual void setLooping(bool looping)   {
    looping_ = looping;
    source_->setLooping(looping);
  }

 private:
  scoped_ptr<AudioSampleBuffer> primaryBuffer_;
  scoped_ptr<Source> source_;
  scoped_ptr<AudioSampleBuffer> buffer_;
  scoped_ptr<Stretcher> stretcher_;
  scoped_ptr<Stretcher> nextStretcher_;

  int position_;
  int offset_;
  int length_;
  bool looping_;

  CriticalSection lock_;
  Description nextDescription_;
  bool rescaleNeeded_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchingSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLE_LOOP__
