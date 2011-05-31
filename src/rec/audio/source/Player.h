#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/audio/Audio.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/source/Timer.h"
#include "rec/audio/source/Level.h"
#include "rec/audio/Device.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio { class Device; }
namespace audio { namespace stretch { class Stretch; }}
namespace audio { class Gain; }

namespace audio {
namespace source {

class Buffered;
class Selection;
class Stereo;
class StereoProto;
class Stretchy;

// Plays an original master source!
// Player has the following source chain:
//   -> timer -> selection ( -> stretchy) -> stereo_ -> level_ -> buffered_ ->
// where the stretchy component will be NULL if no stretch has been requested.
class Player : public Broadcaster<transport::State>,
               public juce::ChangeListener {
 public:
  Player(Device* d);
  virtual ~Player();

  void setState(transport::State state = transport::RUNNING);

  // Source must be pre-prepared.
  void broadcastState() { broadcast(state()); }
  void toggle() { setState(invert(state())); }

  SampleTime getNextReadPosition();
  void setNextReadPosition(SampleTime t);
  RealTime getTime() { return samplesToTime(getNextReadPosition()); }

  transport::State state() const;
  Device* device() { return device_; }
  Broadcaster<SampleTime>* timeBroadcaster() { return timer_; }
  Broadcaster<const LevelVector&>* levelBroadcaster() { return level_; }
  virtual void changeListenerCallback(ChangeBroadcaster*);
  Buffered* buffered() { return buffered_; }
  void setStereoProto(const StereoProto&);
  void setSelection(const block::BlockSet&);
  void setGain(const Gain&);

  SampleTime length() const { return timer_->getTotalLength(); }
  RealTime realLength() const { return audio::samplesToTime(length()); }
  void clearSource();

  void setSource(Source*);
  void setStretch(const stretch::Stretch&);

  static const int BUFFER_SIZE = 2048;

 private:
  CriticalSection lock_;

  AudioTransportSource transportSource_;
  AudioSourcePlayer player_;
  Device* device_;

  ptr<Source> source_;

  Timer* timer_;
  Selection* selection_;
  Stretchy* stretchy_;
  Stereo* stereo_;
  Level* level_;
  Buffered* buffered_;

  DISALLOW_COPY_AND_ASSIGN(Player);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
