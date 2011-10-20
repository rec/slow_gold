#include <map>

#include "rec/base/Arraysize.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/slow/Model.h"
#include "rec/slow/Position.h"
#include "rec/util/Math.h"
#include "rec/util/thread/FunctionCallback.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {
namespace {

typedef void (*LoopSnapshotFunction)(LoopSnapshot*, Position);

void loop(LoopSnapshotFunction lsf, Instance* instance, Position pos) {
  LoopSnapshot snapshot(instance);
  lsf(&snapshot, pos);
  data::set(snapshot.loops_, instance->model_->file());
}

void clearLoops(LoopSnapshot* s, Position) {
  s->loops_.Clear();
  s->loops_.add_loop_point();
}

static void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
  RealTime time = snapshot->loops_.loop_point(segment).time();
  snapshot->instance_->model_->jumpToTime(time);
}

void jump(LoopSnapshot* snap, Position pos) {
  int size = snap->loops_.loop_point_size() - 1;
  int p = positionToIndex(pos, snap->segment_, size);
  setTimeFromSegment(snap, p);
}

void jumpSelected(LoopSnapshot* snap, Position pos) {
  vector<int> selected;
  size_t s;
  bool found = false;
  for (int i = 0; i < snap->loops_.loop_point_size() - 1; ++i) {
    if (!snap->selectionCount_ || snap->loops_.loop_point(i).selected()) {
      if (i == snap->segment_) {
        DCHECK(!found);
        s = selected.size();
        found = true;
      }
      selected.push_back(i);
    }
  }

  DCHECK(found);
  setTimeFromSegment(snap, selected[positionToIndex(pos, s, selected.size())]);
}

void addLoopCallbacks(CallbackTable* t, Instance* i) {
  using thread::functionCallback;
  Position noPos;

  (*t)[Command::CLEAR_LOOPS] = functionCallback(loop, i, clearLoops, noPos);
}
}  // namespace

bool executeLoopCommand(Instance*, const command::Command&);
void toggleSelectionSegment(const VirtualFile&, RealTime);


}  // namespace slow
}  // namespace rec
