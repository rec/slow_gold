#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/util/listener/Listener.h"
#include "rec/util/block/Filler.h"

namespace rec {
namespace audio {

class FillableBuffer : public block::Filler, public Listener<int> {
 public:
  FillableBuffer(PositionableAudioSource* source, int blockSize);
  AudioSampleBuffer* buffer() { return &buffer_; }

  virtual void operator()(int pos) { setPosition(pos); }
	virtual void doFillNextBlock(const block::Block& block);

 protected:
  virtual void onFilled() { source_.reset(); }

 private:
  AudioSampleBuffer buffer_;
  ptr<PositionableAudioSource> source_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FillableBuffer);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
