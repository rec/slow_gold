#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer : public Thread,
                                   public AudioTransportSource,
                                   public juce::ChangeListener {
 public:
  static const int THREAD_WAIT = 10;

  AudioTransportSourcePlayer(AudioDeviceManager* dm);
  virtual ~AudioTransportSourcePlayer();

  // Set to zero and set source to NULL;
  void clear();
  virtual void run();

  void setPosition(double newPosition);

  void toggle() { setStart(!isPlaying()); }
  void setStart(bool isStart = true);
  void update();
  void setOffset(double offset);
  double getCurrentOffsetPosition() const { return getCurrentPosition() + offset_; }

  Broadcaster<double>* doubleBroadcaster() { return &doubleBroadcaster_; }
  Broadcaster<const AudioTransportSourcePlayer&>* changeBroadcaster() {
    return &changeBroadcaster_;
  }

  virtual void changeListenerCallback(ChangeBroadcaster*) {
    // Only triggered on start and stop.
    changeBroadcaster_.broadcast(*this);
  }

 private:
  CriticalSection lock_;
  AudioSourcePlayer player_;
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
