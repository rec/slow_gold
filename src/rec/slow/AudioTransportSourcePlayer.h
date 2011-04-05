#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer : public Thread,
                                   public juce::ChangeListener {
 public:
  static const int THREAD_WAIT = 10;

  AudioTransportSourcePlayer(AudioDeviceManager* dm);
  virtual ~AudioTransportSourcePlayer();

  // Set to zero and set source to NULL;
  void clear();
  virtual void run();

  void broadcastTimeIfChanged();

  void setPosition(double newPosition);

  void toggle() { setStart(!audioTransportSource_.isPlaying()); }
  void setStart(bool isStart = true);
  void setOffset(double offset);

  double getCurrentOffsetPosition() {
    return audioTransportSource()->getCurrentPosition() + offset_;
  }

  Broadcaster<double>* doubleBroadcaster() { return &doubleBroadcaster_; }
  Broadcaster<const AudioTransportSourcePlayer&>* changeBroadcaster() {
    return &changeBroadcaster_;
  }

  virtual void changeListenerCallback(ChangeBroadcaster*) {
    // Only triggered on start and stop.
    changeBroadcaster_.broadcast(*this);
  }

  AudioTransportSource* audioTransportSource() { return &audioTransportSource_; }

 private:
  CriticalSection lock_;

  AudioTransportSource audioTransportSource_;
  AudioSourcePlayer audioSourcePlayer_;
  AudioDeviceManager* deviceManager_;
  Broadcaster<const AudioTransportSourcePlayer&> changeBroadcaster_;
  Broadcaster<double> doubleBroadcaster_;

  double lastTime_;
  double offset_;

  DISALLOW_COPY_AND_ASSIGN(AudioTransportSourcePlayer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
