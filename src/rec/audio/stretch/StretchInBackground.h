#ifndef __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
#define __REC_AUDIO_STRETCH_IN_BACKGROUND_H__

#include "rec/base/scoped_ptr.h"
#include "rec/util/Notifier.h"

namespace rec {
namespace audio {
namespace stretch {

class StretchThread;

class StretchInBackground {
 public:
  typedef rec::audio::timescaler::Description Description;
  typedef rec::util::Notifier<int> Notifier;

  StretchInBackground(const Description& description,
                      const AudioSampleBuffer& source,
                      int sourceSize,
                      int sourcePosition,
                      AudioSampleBuffer* target,
                      Notifier* notifier);

  void start();
  void stop();

  static const char* THREAD_NAME;
  static const int THREAD_PRIORITY;
  static const int INITIAL_SAMPLES;
  static const int CHUNK_SIZE;

 private:
  friend class StretchThread;

  const Description description_;
  const AudioSampleBuffer& source_;
  int sourceSize_;
  int sourcePosition_;
  AudioSampleBuffer* target_;

  scoped_ptr<Thread> thread_;
  scoped_ptr<Notifier> notifier_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(StretchInBackground);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
