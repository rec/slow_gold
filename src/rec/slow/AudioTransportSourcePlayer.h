#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer
  : public Thread,
    public AudioTransportSource,
    public Broadcaster<float>,
    public juce::ChangeListener {
 public:
  static const int THREAD_WAIT = 40;

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

  Broadcaster<const AudioTransportSourcePlayer&>* changeBroadcaster() {
    return &changeBroadcaster_;
  }

  virtual void changeListenerCallback(ChangeBroadcaster*) {
    changeBroadcaster_.broadcast(*this);
  }

 private:
  AudioSourcePlayer player_;
  AudioDeviceManager* deviceManager_;
  Broadcaster<const AudioTransportSourcePlayer&> changeBroadcaster_;
  float lastTime_;
  double offset_;

  DISALLOW_COPY_AND_ASSIGN(AudioTransportSourcePlayer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
