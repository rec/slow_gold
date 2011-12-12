#include "rec/gui/audio/LoopsCuttable.h"

#include "rec/data/yaml/Yaml.h"
#include "rec/gui/audio/Loops.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace gui {
namespace audio {

static const LoopPointList getSelected(Loops* loops, bool sel) {
  return rec::audio::getSelected(loops->getProto(), sel);
}

string LoopsCuttable::copy() const {
  return yaml::write(getSelected(loops_, true));
}

bool LoopsCuttable::canCopy() const {
  return getSelected(loops_, true).loop_point_size();
}

bool LoopsCuttable::canPaste(const string& clipboard) const {
 return true;  // TODO
}

bool LoopsCuttable::canCut() const {
  LoopPointList lpl = getSelected(loops_, true);
  int size = lpl.loop_point_size();
  return (size > 1) || (size == 1 && lpl.loop_point(0).has_time());
}

void LoopsCuttable::cut() {
  LoopPointList lpl = loops_->getProto();
  bool firstWasSelected = lpl.loop_point(0).selected();
  if (lpl.loop_point_size())
    lpl.mutable_loop_point(0)->set_selected(false);
  LoopPointList loops = getSelected(loops_, false);
  if (loops.loop_point_size())
    loops.mutable_loop_point(0)->set_selected(firstWasSelected);

  lpl = loops;
  DLOG(INFO) << loops.ShortDebugString();
  loops_->setValue(lpl);
}

bool LoopsCuttable::paste(const string& s) {
  LoopPointList lpl;
  if (!yaml::read(s, &lpl))
    return false;

  lpl = rec::audio::addLoopPoints(loops_->getProto(), lpl);
  loops_->setValue(lpl);
  return true;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
