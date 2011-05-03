#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/util/listener/Listener.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace audio {
namespace util {

class FillableBuffer : public block::Fillable {
 public:
  FillableBuffer() {}
  void setSource(PositionableAudioSource* source, int blockSize);
  virtual block::Size doFillNextBlock(const block::Block& block);

  AudioSampleBuffer* buffer() { return buffer_.get(); }

 protected:
  virtual void onFilled() { source_.reset(); }

 private:
  ptr<AudioSampleBuffer> buffer_;
  ptr<PositionableAudioSource> source_;
  int64 blockSize_;

  DISALLOW_COPY_AND_ASSIGN(FillableBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
