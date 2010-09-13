#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHY__

// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/stretch/TimeStretch.pb.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchy : public Source {
 public:
  typedef timescaler::TimeStretch TimeStretch;
  const static int MINIMUM_FILL_SIZE = 4096;

  DoubleStretchy(const TimeStretch& description,
                 Source* s0, Source* s1);

  virtual bool fillNext();
  virtual int available() const;
  virtual void setDescription(const TimeStretch& description);

  virtual int getTotalLength() const;
  virtual int getNextReadPosition() const;
  virtual void setNextReadPosition(int position);
  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources();
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
  virtual bool isLooping() const;
  virtual void setLooping(bool looping);

  struct SourceReader {
    scoped_ptr<Source> source_;
    TimeStretch description_;
    int offset_;

    scoped_ptr<Source> reader_;
    scoped_ptr<Buffery> buffered_;

    void reset(const TimeStretch& description, int offset) {
      description_.CopyFrom(description);
      reader_.reset(new Stretchy(description_, source_.get()));
      buffered_.reset(new Buffery(description_.channels(), reader_.get()));
      offset_ = offset;
    }
  };

 private:
  Buffery* source() {
    return source_->buffered_.get();
  }

  const Buffery* source() const {
    return source_->buffered_.get();
  }

  Buffery* next() {
    return nextSource_->buffered_.get();
  }

  bool descriptionChanged_;
  TimeStretch description_;

  int position_;
  CriticalSection lock_;
  int gettingBlock_;

  scoped_ptr<SourceReader> source_;
  scoped_ptr<SourceReader> nextSource_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
