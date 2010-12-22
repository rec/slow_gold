#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace slow {
namespace app {

class AudioTransportSourcePlayer
  : public AudioTransportSource,
    public Thread,
    public listener::Broadcaster<float> {
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

 private:
  AudioSourcePlayer player_;
  AudioDeviceManager* deviceManager_;

  DISALLOW_COPY_AND_ASSIGN(AudioTransportSourcePlayer);
};

}  // namespace app
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
