#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/base/SamplePosition.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/block/Fillable.h"

namespace rec {
namespace audio {

namespace source { class BufferSource; }

namespace util {

class FillableBuffer : public block::Fillable {
 public:
  static const int DEFAULT_BLOCK_SIZE = 4096;

  FillableBuffer() : blockSize_(DEFAULT_BLOCK_SIZE) {}
  void setSource(PositionableAudioSource* source);

  virtual block::Size doFillNextBlock(const block::Block& block);
  void setBlockSize(SamplePosition b) { blockSize_ = b; }

 protected:
  virtual void onFilled() { source_.reset(); }

 private:
  ptr<AudioSampleBuffer> buffer_;
  ptr<PositionableAudioSource> source_;
  int64 blockSize_;

  DISALLOW_COPY_AND_ASSIGN(FillableBuffer);

  friend class audio::source::BufferSource;
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
