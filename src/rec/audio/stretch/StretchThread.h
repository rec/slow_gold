#ifndef __REC_AUDIO_STRETCH_THREAD_H__
#define __REC_AUDIO_STRETCH_THREAD_H__

#include "juce_amalgamated.h"

#include "rec/base/scoped_ptr.h"
#include "rec/util/Notifier.h"
#include "rec/audio/stretch/Description.h"

namespace rec {
namespace audio {
namespace stretch {

class StretchThread : public Thread {
 public:
  static const int PRIORITY = 3;
  static const int INITIAL_SAMPLES = 1024;
  static const int CHUNK_SIZE = 256;

  static const char* NAME;

  StretchThread(Description<float*>* d) : Thread("stretch"), desc_(d) {}

  void start() { Thread::start(PRIORITY);  }

  // ready() is called when INITIAL_SAMPLES worth of data have appeared.
  virtual void ready() = 0;
  virtual void run();

  const Description<float**> getDescription() const { return desc_; }

 protected:
  Description<float**>* desc_;

  DISALLOW_COPY_AND_ASSIGN(StretchThread);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_THREAD_H__
