#ifndef __REC_AUDIO_SOURCE_FRAMESOURCE__
#define __REC_AUDIO_SOURCE_FRAMESOURCE__

#include "rec/audio/util/Frame.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

template <typename Sample, int CHANNELS>
class FrameSource : public PositionableAudioSource {
 public:
  typedef InterleavedFrame<Sample, CHANNELS> SourceFrame;
  typedef Frames<SourceFrame> SourceFrames;

  explicit FrameSource(const SourceFrames& b) : buffer_(b), position_(0) {}
  virtual ~FrameSource() {}

  virtual void getNextAudioBlock(const Info& info) {
    Info i = info;
    while (i.numSamples > 0) {
      int copied = static_cast<int>(buffer_.getAudioBlock(i, position_));
      if (!copied) {
        LOG(DFATAL) << "No samples copied!";
        DCHECK(copied);
        return;
      }
      i.numSamples -= copied;
      i.startSample += copied;

      setNextReadPosition(position_ + copied);
    }
  }

  virtual int64 getTotalLength() const {
    return buffer_.length();
  }

  virtual void setNextReadPosition(int64 p) {
    position_ = mod(p, std::max(1LL, getTotalLength()));
  }

  virtual int64 getNextReadPosition() const { return position_; };
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }

  virtual void prepareToPlay(int, double) {}
  virtual void releaseResources() {}

 private:
  const SourceFrames& buffer_;
  int64 position_;
  bool looping_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(FrameSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_FRAMESOURCE__
