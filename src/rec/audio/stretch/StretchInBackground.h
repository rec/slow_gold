#ifndef __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
#define __REC_AUDIO_STRETCH_IN_BACKGROUND_H__

#include "rec/base/scoped_ptr.h"
#include "rec/util/Notifier.h"

namespace rec {
namespace audio {
namespace stretch {

class StretchThread;

// Possible states for this.
// 1. nothing at all.
// 2. we have a buffer but no first samples
// 3. we have a
class StretchInBackground {
 public:
  const static int BUFFER_WRAPAROUND = 4096;
  const static int EMPTY_BUFFER = 4096;
  StretchInBackground(AudioFormatReader* r)
      : channels_(r->numChannels()),
        sourceLength_(r->lengthInSamples),
        originalBuffer_(channels_, sourceLength_ + BUFFER_WRAPAROUND),
        stretched_(new AudioBuffer(channels_, EMPTY_BUFFER)) {
    original_.readFromAudioReader(r, 0, sourceLength_, 0, true, true);
    stretched_->clear();
  }

  // We're ready to stretch unless we're already stretching in two threads!
  bool readyToStretch() const {
    ScopedLock l(lock_);
    return !nextThread_;
  }

  void changeStretch(const TimeScalerDescription& stretch) {
    ScopedLock l(lock_);
    if (stretchedBuffer_) {
      // We are already working from one buffer.
    } else {
      // First time through.
      stretchedBuffer_.reset(new AudioSampleBuffer(channels_),
                             int(stretch.timescale_ * sourceLength_));
      thread_ = new StretchThread();
      thread_.start();
    }
  }

  void start();
  void stop();

 private:
  scoped_ptr<Thread> thread_, nextThread_;
  CriticalSection lock_;
  const int channels_;
  const int sourceLength_;
  AudioSampleBuffer originalBuffer_;
  scoped_ptr<AudioSampleBuffer> stretchedBuffer_, nextBuffer_;


  friend class StretchThread;

  const Description description_;
  int sourceSize_;
  int sourcePosition_;
  AudioSampleBuffer* target_;

  scoped_ptr<Notifier> notifier_;

  DISALLOW_COPY_AND_ASSIGN(StretchInBackground);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
