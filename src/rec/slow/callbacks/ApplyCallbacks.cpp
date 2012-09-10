#include "rec/slow/callbacks/ApplyCallbacks.h"

#include "rec/audio/Audio.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CallbackTable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/widget/waveform/Viewport.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

namespace {

using audio::AudioSettings;
using audio::Gain;
using command::CallbackTable;
using command::Command;
using widget::waveform::Viewport;

template <typename Proto>
void executeCallbackNoInstance(void (*protoFunction)(Proto*)) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  (*protoFunction)(&proto);
  data::setProto(proto, vf);
}

template <typename Proto>
void executeCallbackIfNoInstance(bool (*protoFunction)(Proto*)) {
  const VirtualFile vf = Instance::getInstanceFile();
  Proto proto(data::getProto<Proto>(vf));
  if ((*protoFunction)(&proto))
    data::setProto(proto, vf);
}

template <typename Proto>
void addApplyCallback(CallbackTable* c, CommandID id,
                      void (*protoFunction)(Proto*)) {
  c->addCallback(id,
                 thread::functionCB(&executeCallbackNoInstance<Proto>,
                                          protoFunction));
}

template <typename Proto>
void addApplyCallback(CallbackTable* c, CommandID id,
                      bool (*protoFunction)(Proto*)) {
  c->addCallback(id,
                 thread::functionCB(&executeCallbackIfNoInstance<Proto>,
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

bool nudgeVolumeDown(Gain* g) { return nudgeVolume(g, false); }
bool nudgeVolumeUp(Gain* g) { return nudgeVolume(g, true); }

void nudgeSpeedDown(Stretch* s) { nudgeSpeed(s, false); }
void nudgeSpeedUp(Stretch* s) { nudgeSpeed(s, true); }

}

void addApplyCallbacks(command::CallbackTable* c) {
  addApplyCallback(c, Command::CLEAR_LOOPS, clearLoops);
  addApplyCallback(c, Command::DIM_VOLUME_TOGGLE, dimVolumeToggle);
  addApplyCallback(c, Command::MUTE_VOLUME_TOGGLE, muteVolumeToggle);
  addApplyCallback(c, Command::NUDGE_VOLUME_DOWN, nudgeVolumeDown);
  addApplyCallback(c, Command::NUDGE_VOLUME_UP, nudgeVolumeUp);
  addApplyCallback(c, Command::NUDGE_SPEED_DOWN, nudgeSpeedDown);
  addApplyCallback(c, Command::NUDGE_SPEED_UP, nudgeSpeedUp);
  addApplyCallback(c, Command::RESET_GAIN_TO_UNITY, resetGainToUnity);
}

}  // namespace slow
}  // namespace rec
