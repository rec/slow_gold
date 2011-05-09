#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Timey.h"
#include "rec/audio/Device.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio { class Device; }

namespace audio {
namespace source {

class Buffered;
class Timey;

class Player : public Broadcaster<transport::State>, public juce::ChangeListener {
 public:
  Player(Device* d);
  virtual ~Player();

  void setState(transport::State state = transport::RUNNING);

  // Source must be pre-prepared.
  void setSource(Source* source);
  void broadcastState() { broadcast(state()); }
  void toggle() { setState(invert(state())); }

  SampleTime getNextReadPosition() { return timer_->getNextReadPosition(); }
  void setNextReadPosition(SampleTime t) { timer_->setNextReadPosition(t); }

  transport::State state() const;
  Device* device() { return device_; }
  Broadcaster<SampleTime>* timeBroadcaster() { return timer_; }
  virtual void changeListenerCallback(ChangeBroadcaster*);
  Buffered* buffered() { return buffered_; }

  static const int BUFFER_SIZE = 2048;

 private:
  CriticalSection lock_;

  AudioTransportSource transportSource_;
  AudioSourcePlayer player_;
  Device* device_;
  Timey* timer_;
  Buffered* buffered_;

  DISALLOW_COPY_AND_ASSIGN(Player);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
