#include "rec/slow/callbacks/ApplyCallbacks.h"

#include "rec/audio/Audio.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/data/Undoable.h"
#include "rec/program/Program.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/widget/waveform/Viewport.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

namespace {

using audio::AudioSettings;
using audio::Gain;
using program::Program;
using widget::waveform::Viewport;

template <typename Proto>
void executeCallback(void (*protoFunction)(Proto*)) {
  const VirtualFile vf = getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto);
  data::setProto(proto, vf);
}

template <typename Proto>
void executeCallbackIf(bool (*protoFunction)(Proto*)) {
  const VirtualFile vf = getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto))
    data::setProto(proto, vf);
}

template <typename Proto>
void addApplyCallback(Program* c, CommandID id,
                      void (*protoFunction)(Proto*)) {
  c->addCallback(id,
                 thread::functionCB(&executeCallback<Proto>,
                                    protoFunction));
}

template <typename Proto>
void addApplyCallback(Program* c, CommandID id,
                      bool (*protoFunction)(Proto*)) {
  c->addCallback(id,
                 thread::functionCB(&executeCallbackIf<Proto>,
                                    protoFunction));
}

void clearLoops(Viewport* viewport) {
  LoopPointList* loops = viewport->mutable_loop_points();
  loops->mutable_loop_point()->Clear();

  LoopPoint* loop = loops->add_loop_point();
  loop->set_selected(true);
  loop->set_time(0);
}

void dimVolumeToggle(Gain* gain) {
  gain->set_dim(!gain->dim());
}

void muteVolumeToggle(Gain* gain) {
  gain->set_mute(!gain->mute());
}

void resetGainToUnity(Gain* gain) {
  gain->set_gain(0);
}

using namespace rec::audio;
using namespace rec::audio::stretch;

template <int semitones>
void nudgePitch(Stretch* s) {
    s->set_semitone_shift(s->semitone_shift() + semitones);
}

bool nudgeVolume(Gain* gain, bool isInc) {
  if (gain->dim() || gain->mute())
    return false;

  double inc = data::getProto<AudioSettings>().volume_nudge_db();
  gain->set_gain(gain->gain() + (isInc ? inc : -inc));
  return true;
}

void nudgeSpeed(Stretch* stretch, bool isInc) {
  double nudge = data::getProto<AudioSettings>().speed_nudge_percent() / 100.0;
  double scale = isInc ? (1.0 + nudge) : 1.0 / (1.0 + nudge);
  stretch->set_time_percent(stretch->time_percent() * scale);
}

void nudgeSpeedDown(Stretch* s) { nudgeSpeed(s, false); }
void nudgeSpeedUp(Stretch* s) { nudgeSpeed(s, true); }

bool nudgeVolumeDown(Gain* g) { return nudgeVolume(g, false); }
bool nudgeVolumeUp(Gain* g) { return nudgeVolume(g, true); }

}

void addApplyCallbacks(program::Program* c) {
  addApplyCallback(c, slow::Command::CLEAR_LOOPS, clearLoops);
  addApplyCallback(c, slow::Command::DIM_VOLUME_TOGGLE, dimVolumeToggle);
  addApplyCallback(c, slow::Command::MUTE_VOLUME_TOGGLE, muteVolumeToggle);
  addApplyCallback(c, slow::Command::NUDGE_PITCH_DOWN, nudgePitch<-1>);
  addApplyCallback(c, slow::Command::NUDGE_PITCH_UP, nudgePitch<1>);
  addApplyCallback(c, slow::Command::NUDGE_SPEED_DOWN, nudgeSpeedDown);
  addApplyCallback(c, slow::Command::NUDGE_SPEED_UP, nudgeSpeedUp);
  addApplyCallback(c, slow::Command::NUDGE_VOLUME_DOWN, nudgeVolumeDown);
  addApplyCallback(c, slow::Command::NUDGE_VOLUME_UP, nudgeVolumeUp);
  addApplyCallback(c, slow::Command::RESET_GAIN_TO_UNITY, resetGainToUnity);
}

}  // namespace slow
}  // namespace rec
