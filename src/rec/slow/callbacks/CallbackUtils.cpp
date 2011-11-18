#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/BufferFiller.h"

namespace rec {
namespace slow {

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, Position);

void loop(Instance* instance, LoopSnapshotFunction lsf, Position pos) {
  LoopSnapshot snapshot(instance);
  lsf(&snapshot, pos);
  data::set(snapshot.loops_, instance->file());
}

void select(Instance* instance, SelectorFunction selector, Position pos) {
  LoopSnapshot snap(instance);
  LoopPointList* loops = &snap.loops_;
  int size = loops->loop_point_size();
  int p = pos.toIndex(snap.segment_, size - 1);

  bool allSelected = (snap.selectionCount_ == size);

  for (int i = 0; i < size; ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(selector(i, p, lp->selected(), allSelected));
  }
  data::set(snap.loops_, instance->file());
}

}  // namespace slow
}  // namespace rec
