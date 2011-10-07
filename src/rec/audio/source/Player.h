#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/Level.h"
#include "rec/audio/source/Timer.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/block/Block.h"
#include "rec/util/listener/DataListener.h"

namespace rec {

namespace audio { class Device; }
namespace audio { namespace stretch { class Stretch; }}
namespace audio { class Gain; }

namespace audio {
namespace source {

class Selection;
class Stereo;
class StereoProto;
class Stretchy;

// Plays an original master source!
// Player has the following source chain:
//   -> timer -> selection ( -> stretchy) -> stereo_ -> level_ -> buffered_ ->
// where the stretchy component will be NULL if no stretch has been requested.
class Player : public Broadcaster<transport::State>,
               public DataListener<Gain>,
               public DataListener<LoopPointList>,
               public DataListener<StereoProto>,
               public juce::ChangeListener {
 public:
  Player(Device* d);
  virtual ~Player();

  void setState(transport::State state = transport::RUNNING);

  // Source must be pre-prepared.
  void broadcastState() { broadcast(state()); }
  void toggle() { setState(invert(state())); }

  SamplePosition getNextReadPosition();
  void setNextReadPosition(int64 t);
  RealTime getTime() { return getNextReadPosition(); }

  transport::State state() const;
  Device* device() { return device_; }
  Broadcaster<SamplePosition>* timeBroadcaster() { return timer_; }
  Level* level() { return &level_; }
  virtual void changeListenerCallback(ChangeBroadcaster*);

  virtual void onDataChange(const Gain&);
  virtual void onDataChange(const StereoProto&);
  virtual void onDataChange(const LoopPointList&);

  void setGain(double);

  SamplePosition length() const { return timer_->getTotalLength(); }
  void clear();
  void setStretch(const stretch::Stretch&);
  void setSource(Source*);
  void setSelection(const block::BlockSet& s);

 private:
  CriticalSection lock_;

  AudioTransportSource transportSource_;
  AudioSourcePlayer player_;
  Device* device_;

  Timer* timer_;
  Selection* selection_;
  Stretchy* stretchy_;
  Stereo* stereo_;
  Level level_;

  DISALLOW_COPY_AND_ASSIGN(Player);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
