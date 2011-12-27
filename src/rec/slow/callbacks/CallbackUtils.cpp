#include "rec/slow/callbacks/CallbackUtils.h"

#include "rec/data/DataOps.h"
#include "rec/slow/BufferFiller.h"

namespace rec {
namespace slow {

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, CommandIDEncoder);

void loop(Instance* instance, LoopSnapshotFunction lsf, CommandIDEncoder pos) {
  LoopSnapshot snapshot(instance);
  lsf(&snapshot, pos);
  instance->setProto(snapshot.loops_);
}

void select(Instance* instance, SelectorFunction selector, CommandIDEncoder pos) {
  LoopSnapshot snap(instance);
  LoopPointList* loops = &snap.loops_;
  int segment = audio::getSegment(*loops, snap.instance_->time());
  int size = loops->loop_point_size();
  int p = pos.toIndex(segment, size);


  bool allSelected = (audio::getSelectionCount(snap.loops_) == size);

  for (int i = 0; i < size; ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(selector(i, p, lp->selected(), allSelected));
  }
  instance->setProto(snap.loops_);
}

}  // namespace slow
}  // namespace rec
