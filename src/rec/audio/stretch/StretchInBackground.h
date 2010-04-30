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
  StretchInBackground(const Description& description,
                      const AudioSampleBuffer& source,
                      int sourcePosition,
                      AudioSampleBuffer* target,
                      rec::util::Notifier* notifier = NULL)
      : description_(description),
        source_(source),
        sourcePosition_(sourcePosition),
        target_(target),
        notifier_(notifier) {
  }

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
  int sourcePosition_;
  AudioSampleBuffer* target_;

  scoped_ptr<Thread> thread_;
  scoped_ptr<rec::util::Notifier> notifier_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(StretchInBackground);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
