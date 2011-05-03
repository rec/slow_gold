#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/util/listener/Listener.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace audio {
namespace util {

class FillableBuffer : public block::Fillable {
 public:
  FillableBuffer(PositionableAudioSource* source, int blockSize);
  AudioSampleBuffer* buffer() { return &buffer_; }

  virtual block::Size doFillNextBlock(const block::Block& block);

 protected:
  virtual void onFilled() { source_.reset(); }

 private:
  AudioSampleBuffer buffer_;
  ptr<PositionableAudioSource> source_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FillableBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
