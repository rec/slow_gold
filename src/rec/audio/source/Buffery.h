#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Circular.h"
#include "rec/util/block/Block.h"
#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace audio {
namespace source {

class Buffery {
 public:
  Buffery(PositionableAudioSource* source, int blockSize);

  AudioSampleBuffer* buffer() { return &buffer_; }

  void setPosition(int position);
  bool hasFilled(Block b) const;
  bool fill();

 private:
  Block firstEmptyBlock(int position = -1) const;

  CriticalSection lock_;
  const int length_;
  AudioSampleBuffer buffer_;
  scoped_ptr<PositionableAudioSource> source_;
  BlockSet filled_;
  int position_;
  const int blockSize_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Buffery);
};

#if 0

AudioSourceChannelInfo makeInfo(const Block& block, AudioSampleBuffer* buffer);

struct FilledBuffer {
  AudioSampleBuffer* buffer_;
  BlockSet filled_;
};


class BufferUpdated : public listener::Listener<const AudioSourceChannelInfo&> {
 public:
  explicit Buffery(AudioSampleBuffer* buffer, BlockSet* filled)
      : buffer_(buffer), filled_(filled) {
  }

  void operator()(const AudioSourceChannelInfo& info) {

  }
};


// Buffer an entire file in memory.
class Buffery : public listener::Listener<const AudioSourceChannelInfo&> {
 public:
  explicit Buffery(AudioSampleBuffer* buffer) : buffer_(buffer) {}
  void operator()(const AudioSourceChannelInfo& info) {

  }

  typedef util::block::Block Block;
  typedef util::block::BlockSet BlockSet;

  // Buffery owns its source.
  Buffery(PositionableAudioSource* source, int blockSize);
  ~Buffery();

  int getAudioBlock(const AudioSourceChannelInfo& info, int position);
  void ensureAudioBlock(const AudioSourceChannelInfo& info, int position);

  int getTotalLength() const { return length_; }
  void setReadPosition(int p) { position_ = p; }
  bool isFull() const { return isFull_; }

  bool fillBlocksCovering(const Block& block);
  bool fillNextEmptyBlock();

 protected:
  virtual bool fill(const Block& block, const AudioSourceChannelInfo& info);
  bool fill(const Block& block);

 private:
  scoped_ptr<PositionableAudioSource> source_;

  // Maps out the areas that are already full.
  BlockSet filled_;
  const int length_;
  AudioSampleBuffer buffer_;
  bool isFull_;
  const int blockSize_;
  int position_;

#ifdef USE_MALLOC_FOR_BUFFERY
  float* sampleData_[2];
#endif

  DISALLOW_COPY_AND_ASSIGN(Buffery);
};
#endif
}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
