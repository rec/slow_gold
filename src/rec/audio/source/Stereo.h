#pragma once

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Stereo.pb.h"

namespace rec {
namespace audio {
namespace source {

class Stereo : public Wrappy {
 public:
  Stereo(PositionableAudioSource* source,
         const StereoProto& desc = StereoProto::default_instance());

  void setStereo(const StereoProto&);
  StereoProto getStereo() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&);

 private:
  StereoProto desc_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Stereo);
};

void fixStereo(StereoProto*);

}  // namespace source
}  // namespace audio
}  // namespace rec

