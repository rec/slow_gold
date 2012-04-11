#ifndef __REC_AUDIO_SOURCE_STEREO__
#define __REC_AUDIO_SOURCE_STEREO__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Stereo.pb.h"

namespace rec {
namespace audio {
namespace source {

class Stereo : public Wrappy {
 public:
  Stereo(PositionableAudioSource* source,
         const StereoProto& desc = StereoProto::default_instance())
      : Wrappy(source), desc_(desc) {
  }

  void setStereo(const StereoProto&);
  StereoProto getStereo() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&);

 private:
  StereoProto desc_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Stereo);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STEREO__
