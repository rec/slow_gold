#include "rec/gui/audio/LoopsCuttable.h"

#include "rec/data/yaml/Yaml.h"
#include "rec/gui/audio/Loops.h"
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace gui {
namespace audio {

namespace {

using rec::widget::waveform::Viewport;

const LoopPointList getSelected(const LoopPointList& lpl, bool sel) {
  return rec::audio::getSelected(lpl, sel);
}

const LoopPointList getSelected(const Loops& loops, bool sel) {
  return getSelected(loops.getProto().loop_points(), sel);
}

}  // namespace

string LoopsCuttable::copy() const {
  return yaml::write(getSelected(*loops_, true));
}

bool LoopsCuttable::canCopy() const {
  return getSelected(*loops_, true).loop_point_size() > 0;
}

bool LoopsCuttable::canPaste(const string& s) const {
  LoopPointList lpl;
  return yaml::read(s, &lpl);
}

bool LoopsCuttable::canCut() const {
  LoopPointList lpl = getSelected(*loops_, true);
  int size = lpl.loop_point_size();
  return (size > 1) || (size == 1 && lpl.loop_point(0).has_time());
}

void LoopsCuttable::cut() {
  Viewport vp = loops_->getProto();
  LoopPointList lpl = rec::audio::cutSelected(vp.loop_points(), true);
  vp.mutable_loop_points()->CopyFrom(lpl);
  loops_->editViewport(vp);
}

bool LoopsCuttable::paste(const string& s) {
  using rec::audio::addLoopPoints;

  Viewport vp;
  if (!yaml::read(s, &vp))
    return false;

  Viewport vp2 = loops_->getProto();
  LoopPointList lpl = addLoopPoints(vp.loop_points(), vp2.loop_points());
  vp2.mutable_loop_points()->CopyFrom(lpl);
  loops_->editViewport(vp2);
  return true;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
