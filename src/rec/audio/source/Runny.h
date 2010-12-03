#ifndef __REC_AUDIO_SOURCE_RUNNY__
#define __REC_AUDIO_SOURCE_RUNNY__

#include "rec/base/base.h"

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

class Runny : public Wrappy::Position {
 public:
  static const int BUFFER_SIZE = 200000;
  static const int MIN_BUFFER_SIZE = 16384;
  static const int CHUNK_SIZE = 1024;

  Runny(Source* source,
        int bufferSize = BUFFER_SIZE,
        int minBufferSize = MIN_BUFFER_SIZE,
        int chunkSize = CHUNK_SIZE);

  virtual ~Runny();

  virtual bool isReady();
  virtual void setNextReadPosition(int p);
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

  // Try to pre-fill the lookahead buffer.
  // Return true when the buffer is full, false otherwise.
  bool fill();

  // Make a thread that calls fill() repeatedly.
  Thread* makeThread(int wait);

 private:
  CriticalSection lock_;
  AudioSampleBuffer buffer_;
  util::Circular filled_;
  const int minBufferSize_;
  const int chunkSize_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Runny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_RUNNY__
