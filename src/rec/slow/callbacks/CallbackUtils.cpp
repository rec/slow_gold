#include "rec/slow/callbacks/CallbackUtils.h"

#include "rec/data/DataOps.h"
#include "rec/slow/CurrentTime.h"

namespace rec {
namespace slow {

void loopInstance(Instance* instance, LoopSnapshotFunction lsf, CommandIDEncoder pos) {
  loopNoInstance(lsf, pos);
}

void selectInstance(Instance* instance, SelectorFunction selector, CommandIDEncoder pos) {
  selectNoInstance(selector, pos);
}

void loopNoInstance(LoopSnapshotFunction lsf, CommandIDEncoder pos) {
  Instance* instance = Instance::getInstance();
  LoopSnapshot snapshot(instance);
  lsf(&snapshot, pos);
  instance->setProto(snapshot.viewport_);
  instance->currentTime_->zoomToCurrentTime();
}

void selectNoInstance(SelectorFunction selector, CommandIDEncoder pos) {
  Instance* instance = Instance::getInstance();
  LoopSnapshot snap(instance);
  LoopPointList* loops = snap.loops_;
  int segment = audio::getSegment(*loops, snap.instance_->time());
  int size = loops->loop_point_size();
  int p = pos.toIndex(segment, size);

  bool multipleSelections = (audio::getSelectionCount(*snap.loops_) > 1);

  for (int i = 0; i < size; ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(selector(i, p, lp->selected(), multipleSelections));
  }
  instance->setProto(snap.viewport_);
}

}  // namespace slow
}  // namespace rec
