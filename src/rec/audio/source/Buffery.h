#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/util/listener/Listener.h"
#include "rec/util/block/Filler.h"

namespace rec {
namespace audio {
namespace source {

class Buffery : public block::Filler, public Listener<int> {
 public:
  Buffery(PositionableAudioSource* source, int blockSize);
  AudioSampleBuffer* buffer() { return &buffer_; }

  virtual void operator()(int pos) { setPosition(pos); }
	virtual void doFillNextBlock(const block::Block& block);

 private:
  AudioSampleBuffer buffer_;
  ptr<PositionableAudioSource> source_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Buffery);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
