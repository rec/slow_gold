#pragma once

#include "rec/audio/Audio.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/Level.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/source/Timer.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/util/Gain.h"
#include "rec/data/DataListener.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec { namespace audio { class PlayState; }}

namespace rec {
namespace audio {
namespace source {

class Selection;
class Stereo;
class StereoProto;

// Plays an original master source!
// Player has the following source chain:
//   -> timer -> selection ( -> stretchy) -> stereo_ -> level_ -> buffered_ ->
// where the stretchy component will be nullptr if no stretch has been requested.
class Player : public DataListener<AudioSettings>,
               public DataListener<Gain>,
               public DataListener<PlayState>,
               public DataListener<StereoProto>,
               public DataListener<stretch::Stretch>,
               public DataListener<widget::waveform::Viewport>,
               public Listener<SampleRate>,
               public juce::ChangeListener {
 public:
  Player(Device* d);

  void init();
  virtual ~Player();

  void setState(transport::State state);

  void broadcastTransportState();
  void toggle() { setState(invert(state())); }
  void start() { setState(transport::RUNNING); }

  void setNextReadPosition(const SampleTime&);
  SampleTime getNextReadPosition();
  SampleTime getTime() { return getNextReadPosition(); }

  transport::State state() const;
  Device* device() { return device_; }
  Level* level() { return &level_; }
  Timer* timer() { return timer_; }
  stretch::Stretchy* stretchy() { return stretchy_; }

  Source* makeSourceCopy(Source* s, bool useSelection);

  void changeListenerCallback(ChangeBroadcaster*) override;
  void operator()(SampleRate outputSampleRate) override;
  void operator()(const AudioSettings&) override;
  void operator()(const Gain&) override;
  void operator()(const PlayState& s) override;
  void operator()(const StereoProto&) override;
  void operator()(const stretch::Stretch&) override;
  void operator()(const widget::waveform::Viewport&) override;

  void setGain(double);
  void setSource(Source*);

  // Stop the player and reset the position to 0.
  void reset();

  SampleTime getSelectionLength() const;
  void setInputSampleRate(SampleRate);

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

