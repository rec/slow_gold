#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHY__

// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/stretch/description.pb.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchy : public PositionableAudioSource {
 public:
  typedef rec::audio::timescaler::Description Description;
  const static int MINIMUM_FILL_SIZE = 4096;

  DoubleStretchy(const Description& description,
                 PositionableAudioSource* s0, PositionableAudioSource* s1);

  virtual bool fillNext();
  virtual int available() const;
  void setDescription(const Description& description);

  virtual int getTotalLength() const;
  virtual int getNextReadPosition() const;
  virtual void setNextReadPosition(int position);
  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources();
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
  virtual bool isLooping() const;
  virtual void setLooping(bool looping);

 private:
  struct SourceReader {
    scoped_ptr<PositionableAudioSource> source_;
    Description description_;
    int offset_;

    scoped_ptr<PositionableAudioSource> reader_;
    scoped_ptr<Buffery> buffered_;

    void reset(const Description& description, int offset) {
      description_.CopyFrom(description);
      reader_.reset(new Stretchy(description_, source_.get()));
      buffered_.reset(new Buffery(description_.channels(), reader_.get()));
      offset_ = offset;
    }
  };

  Buffery* source() {
    return readers_[currentReader_].buffered_.get();
  }

  const Buffery* source() const {
    return readers_[currentReader_].buffered_.get();
  }

  Buffery* next() {
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


class DoubleStretchyThread : public DoubleStretchy, Thread {
 public:
  typedef rec::audio::timescaler::Description Description;

  DoubleStretchyThread(const Description& d,
                       PositionableAudioSource* s0, PositionableAudioSource* s1)
      : DoubleStretchy(d, s0, s1),
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
