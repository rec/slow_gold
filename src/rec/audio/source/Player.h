#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

// Player is a non-GUI element with:
// * AudioTransportSource
// * AudioSourcePlayer

class Player : public Broadcaster<TransportState>, public juce::ChangeListener {
 public:
  Player(Device* d);
  virtual ~Player();

  void setTransportState(TransportState state = RUNNING);

  void setSource(Source* source);
  void broadcastState() { broadcast(state()); }
  void toggle() { setState(not(state())); }
  SampleTime getNextReadPosition() const {
    return transport_.getNextReadPosition();
  }

  TransportState state() const;
  virtual void changeListenerCallback(ChangeBroadcaster*);
  Device* device() { return device_; }

 private:
  CriticalSection lock_;

  AudioTransportSource transport_;
  AudioSourcePlayer player_;
  Device* device_;
  ptr<Source> source_;

  DISALLOW_COPY_AND_ASSIGN(Player);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
