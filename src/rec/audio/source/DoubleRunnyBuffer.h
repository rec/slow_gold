#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
#define __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__

#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/BufferySource.h"
#include "rec/audio/source/CachedThumbnail.h"
#include "rec/audio/source/DoubleRunny.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunnyBuffer : public DoubleRunny, public Thread {
 public:
  DoubleRunnyBuffer(const VolumeFile& file, int blockSize);

  static const int READAHEAD = 20000;
  static const int WAIT_TIME = 20;
  static const int MAX_WAIT_TIME = 1000;

  virtual void setPosition(int pos) { buffery_.setPosition(pos); }

  virtual PositionableAudioSource* makeSource(const VolumeFile& f);
  juce::AudioThumbnail* thumbnail() { return cachedThumbnail_.thumbnail(); }

  virtual void run();

 private:
  CachedThumbnail cachedThumbnail_;
  Buffery buffery_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunnyBuffer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
