#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/Model.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
  RealTime time = snapshot->loops_.loop_point(segment).time();
  snapshot->instance_->model_->jumpToTime(time);
}

void jump(LoopSnapshot* snap, Position pos) {
  int size = snap->loops_.loop_point_size() - 1;
  int p = positionToIndex(pos, snap->segment_, size);
  snap->loops_.mutable_loop_point(p)->set_selected(true);
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

bool selectAdd(int index, int pos, bool sel, bool) { return sel || index == pos; }
bool selectOnly(int index, int pos, bool, bool) { return index == pos; }
bool toggle(int index, int pos, bool sel, bool) { return sel != (index == pos); }
bool unselect(int index, int pos, bool sel, bool) { return sel && index != pos; }

}  // namespace

void add(CallbackTable* c, int32 type, Position position,
            SelectorFunction f, Instance* i) {
  add(c, type * Command::BANK_SIZE + position - FIRST, select, i, f, position);
}

void add(CallbackTable* c, int32 type, Position position,
             LoopSnapshotFunction f, Instance* i) {
  add(c, type * Command::BANK_SIZE + position - FIRST, loop, i, f, position);
}

void addRepeatedCallbacks(CallbackTable* t, Instance* i, int repeat) {
  for (int j = FIRST; j < repeat; ++j) {
  	Position pos = static_cast<Position>(j);
    add(t, Command::SELECT, pos, selectAdd, i);
    add(t, Command::SELECT_ONLY, pos, selectOnly, i);
    add(t, Command::TOGGLE, pos, toggle, i);
    add(t, Command::UNSELECT, pos, unselect, i);

    add(t, Command::JUMP_SELECTED, pos, jumpSelected, i);
    add(t, Command::JUMP, pos, jump, i);
  }
}

}  // namespace slow
}  // namespace rec
