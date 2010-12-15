#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Circular.h"
#include "rec/util/block/Block.h"
#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace audio {
namespace source {

class Buffery : public listener::Listener<int> {
 public:
  Buffery(PositionableAudioSource* source, int blockSize);

  AudioSampleBuffer* buffer() { return &buffer_; }

  virtual void operator()(int pos) { setPosition(pos); }
  void setPosition(int position);
  bool hasFilled(int length) const;
  bool hasFilled(const Block& b) const;
  void fillNextBlock();
  bool isFull() const;

 private:
  CriticalSection lock_;
  const int length_;
  AudioSampleBuffer buffer_;
  scoped_ptr<PositionableAudioSource> source_;
  BlockSet filled_;
  int position_;
  const int blockSize_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Buffery);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
