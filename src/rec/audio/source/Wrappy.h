#ifndef __REC_AUDIO_SOURCE_WRAPPY__
#define __REC_AUDIO_SOURCE_WRAPPY__

#include <vector>

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {
namespace source {

class Wrappy : public PositionableAudioSource {
 public:
  explicit Wrappy(PositionableAudioSource* s = NULL);
  virtual int64 getTotalLength() const { return source()->getTotalLength(); }

  virtual bool isLooping() const { return source()->isLooping(); }
  virtual void setLooping(bool looping) { source()->setLooping(looping); }

  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources() { source()->releaseResources(); }

  SamplePosition mod(SamplePosition x) const;

  virtual int64 getNextReadPosition() const;
  virtual void setNextReadPosition(int64 p);
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

  virtual PositionableAudioSource* source() const;
  virtual void setSource(PositionableAudioSource* s);
  void swap(ptr<PositionableAudioSource>* other);

 protected:
  virtual PositionableAudioSource* getSource() const;
  CriticalSection lock_;

  SamplePosition position_;
  ptr<PositionableAudioSource> source_;

  bool prepared_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
