#ifndef __REC_AUDIO_SOURCE_TRACKSOURCE__
#define __REC_AUDIO_SOURCE_TRACKSOURCE__

#include "rec/audio/source/Source.h"

namespace rec {
namespace audio {
namespace source {

class BufferySourceFactory;

class TrackSource : public PositionableAudioSource {
 public:
  TrackSource(BufferySourceFactory* f, int offset = 0);
  virtual ~TrackSource() { release(); }

  void release();

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
  virtual int getTotalLength() const;
  virtual int getNextReadPosition() const;
  virtual void setNextReadPosition(int p);
  virtual bool isLooping() const { return true; }
  virtual void setLooping(bool looping) {}

  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}
  void clearFactory();

  CriticalSection& lock() { return factory_->lock(); }

 private:
  BufferySourceFactory* factory_;

  const int offset_;
  CriticalSection lock_;
  int position_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TrackSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_TRACKSOURCE__
