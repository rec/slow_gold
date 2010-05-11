#ifndef __REC_BUFFERED_AUDIO_SOURCE
#define __REC_BUFFERED_AUDIO_SOURCE

#include <vector>

#include "juce_amalgamated.h"

#include "rec/audio/FillQueue.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

struct BufferDescription {
  int channels;
  int bufferCount;
  int priority;
  int samples;
  int wait;
  int waitForShutdown;

  static BufferDescription DEFAULT;
};

class Buffered : public AudioSource, public Thread {
 public:
  Buffered(const String& threadName, const BufferDescription& d);
  ~Buffered();

  virtual void fillOneBuffer(AudioSampleBuffer *toFill) = 0;

  virtual void run();
  virtual void shutdown();

  virtual void init();
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

  virtual void releaseResources() {}

  virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}

 protected:
  const BufferDescription desc_;

 private:
  virtual void fillBuffers();

  typedef std::vector<AudioSampleBuffer*> BufferList;

  BufferList buffers_;
  rec::audio::buffer::FillQueue queue_;
  Buffered* wrapper_;

  int bufferBeingStreamed_;
  int offset_;
  CriticalSection lock_;
  int minBuffers_;
  int wait_;

  DISALLOW_COPY_AND_ASSIGN(Buffered);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_BUFFERED_AUDIO_SOURCE
