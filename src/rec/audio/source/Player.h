#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Timey.h"
#include "rec/audio/Device.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

// Player is a non-GUI element with:
// * AudioTransportSource
// * AudioSourcePlayer

class Player : public Broadcaster<transport::State>, public juce::ChangeListener {
 public:
  Player(Device* d);
  virtual ~Player();

  void setState(transport::State state = transport::RUNNING);

  void setSource(Source* source);
  void broadcastState() { broadcast(state()); }
  void toggle() { setState(invert(state())); }

  SampleTime getNextReadPosition() const {
    return transportSource_.getNextReadPosition();
  }

  transport::State state() const;
  virtual void changeListenerCallback(ChangeBroadcaster*);
  Device* device() { return device_; }
  Broadcaster<SampleTime>* timeBroadcaster() { return &timer_; }

 private:
  CriticalSection lock_;

  ptr<Source> source_;
  AudioTransportSource transportSource_;
  AudioSourcePlayer player_;
  Device* device_;
  Timey timer_;

  DISALLOW_COPY_AND_ASSIGN(Player);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
