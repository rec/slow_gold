#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Circular.h"
#include "rec/util/block/Block.h"
#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace audio {
namespace source {

// #define USE_MALLOC_FOR_BUFFERY

class Buffery : public listener::Broadcaster<const Buffery&>, public Thread {
 public:
  typedef util::block::Block Block;
  typedef util::block::BlockSet BlockSet;

  // Buffery owns its source.
  Buffery(Source* source, int blockSize);
  ~Buffery();

  virtual void run();
  void setReadPosition(int newPosition);

  bool fillBlocksCovering(const Block& block);
  bool fillNextEmptyBlock();
  bool isFull() const;

  int getAudioBlock(const AudioSourceChannelInfo& info, int position);
  int getTotalLength() const { return source_->getTotalLength(); }

 protected:
  virtual bool fill(const AudioSourceChannelInfo& info);

 private:
  bool fill(const Block& block);

  // Maps out the areas that are already full.
  CriticalSection lock_;
  Source* source_;
  BlockSet filled_;
  AudioSampleBuffer buffer_;
  bool isFull_;
  const int blockSize_;
  int position_;

#ifdef USE_MALLOC_FOR_BUFFERY
  float* sampleData_[2];
#endif

  DISALLOW_COPY_AND_ASSIGN(Buffery);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
