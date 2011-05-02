#ifndef __REC_AUDIO_SOURCE_WRAPPY__
#define __REC_AUDIO_SOURCE_WRAPPY__

#include <vector>

#include "rec/audio/source/Empty.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class Wrappy : public PositionableAudioSource {
 public:
  explicit Wrappy(PositionableAudioSource* s);
  virtual SampleTime getTotalLength() const { return source()->getTotalLength(); }

  virtual bool isLooping() const { return source()->isLooping(); }
  virtual void setLooping(bool looping) { source()->setLooping(looping); }

  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources() { source()->releaseResources(); }

  int mod(SampleTime x) const { return rec::util::mod(x, getTotalLength()); }

  virtual SampleTime getNextReadPosition() const;
  virtual void setNextReadPosition(SampleTime p);
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

  virtual PositionableAudioSource* source() const;
  virtual void setSource(PositionableAudioSource* s);

 protected:
  virtual PositionableAudioSource* getSource() const { return source_.get(); }
  CriticalSection lock_;

  SampleTime position_;
  ptr<PositionableAudioSource> source_;

  bool prepared_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
