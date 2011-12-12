#include "rec/gui/audio/LoopsCuttable.h"

#include "rec/data/yaml/Yaml.h"
#include "rec/gui/audio/Loops.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace gui {
namespace audio {

namespace {

const LoopPointList getSelected(const LoopPointList& lpl, bool sel) {
  return rec::audio::getSelected(lpl, sel);
}

const LoopPointList getSelected(const Loops& loops, bool sel) {
  return getSelected(loops.getProto(), sel);
}

}  // namespace

string LoopsCuttable::copy() const {
  return yaml::write(getSelected(*loops_, true));
}

bool LoopsCuttable::canCopy() const {
  return getSelected(*loops_, true).loop_point_size();
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
  loops_->editLoopPoints(rec::audio::cutSelected(loops_->getProto(), true));
}

bool LoopsCuttable::paste(const string& s) {
  using rec::audio::addLoopPoints;

  LoopPointList lpl;
  if (!yaml::read(s, &lpl))
    return false;

  loops_->editLoopPoints(addLoopPoints(loops_->getProto(), lpl));
  return true;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
