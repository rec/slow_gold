#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Circular.h"
#include "rec/util/block/Block.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

class Buffery : public listener::Listener<int>,
                public listener::Broadcaster<const Buffery&> {
 public:
  Buffery(PositionableAudioSource* source, int blockSize);

  AudioSampleBuffer* buffer() { return &buffer_; }

  virtual void operator()(int pos) { setPosition(pos); }
  void setPosition(int position);
  bool hasFilled(int length) const;
  bool hasFilled(const block::Block& b) const;
  void fillNextBlock();
  bool isFull() const;
  int getLength() const { return length_; }
  bool waitUntilFilled(int length, int waitTime = 40, int maxTime = 10000);

 private:
  CriticalSection lock_;
  const int length_;
  AudioSampleBuffer buffer_;
  int position_;
  ptr<PositionableAudioSource> source_;
  const int blockSize_;
  block::BlockSet filled_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Buffery);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
