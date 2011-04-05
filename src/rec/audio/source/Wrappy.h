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
  Wrappy(PositionableAudioSource* s);
  virtual int64 getTotalLength() const { return source()->getTotalLength(); }

  virtual bool isLooping() const { return source()->isLooping(); }
  virtual void setLooping(bool looping) { source()->setLooping(looping); }

  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources() { source()->releaseResources(); }

  int mod(int64 x) const { return util::mod(x, getTotalLength()); }

  virtual int64 getNextReadPosition() const;
  virtual PositionableAudioSource* source() const;
  virtual void setSource(PositionableAudioSource* s);
  virtual void setNextReadPosition(int64 p);
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

 protected:
  virtual PositionableAudioSource* getSource() const { return source_.get(); }
  CriticalSection lock_;

  int64 position_;
  ptr<PositionableAudioSource> source_;

  bool prepared_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
