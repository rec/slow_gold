#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/Level.h"
#include "rec/audio/source/Timer.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/data/DataListener.h"
#include "rec/util/LoopPoint.h"

namespace rec {

namespace audio { class Device; }
namespace audio { namespace stretch { class Stretch; }}
namespace audio { namespace stretch { class Stretchy; }}
namespace audio { class Gain; }

namespace audio {
namespace source {

class Selection;
class Stereo;
class StereoProto;

// Plays an original master source!
// Player has the following source chain:
//   -> timer -> selection ( -> stretchy) -> stereo_ -> level_ -> buffered_ ->
// where the stretchy component will be NULL if no stretch has been requested.
class Player : public DataListener<Gain>,
               public DataListener<stretch::Stretch>,
               public DataListener<StereoProto>,
               public Broadcaster<transport::State>,
               public juce::ChangeListener {
 public:
  Player(Device* d);
  virtual ~Player();

  void startListening();

  void setState(transport::State state);

  // Source must be pre-prepared.  TODO:  what does this mean?
  void broadcastState();
  void toggle() { setState(invert(state())); }

  void setNextReadPosition(const Samples<44100>&);
  Samples<44100> getNextReadPosition();
  Samples<44100> getTime() { return getNextReadPosition(); }

  transport::State state() const;
  Device* device() { return device_; }
  Level* level() { return &level_; }
  Timer* timer() { return timer_; }

  virtual void changeListenerCallback(ChangeBroadcaster*);

  virtual void operator()(const Gain&);
  virtual void operator()(const StereoProto&);
  virtual void operator()(const stretch::Stretch&);

  void setGain(double);

  void setSource(Source*);
  void clear();

 private:
  CriticalSection lock_;

  AudioTransportSource transportSource_;
  AudioSourcePlayer player_;
  Device* device_;

  Timer* timer_;
  Selection* selection_;
  stretch::Stretchy* stretchy_;
  Stereo* stereo_;
  Level level_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Player);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
