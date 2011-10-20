#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/slow/callbacks/Callbacks.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
  RealTime time = snapshot->loops_.loop_point(segment).time();
  snapshot->instance_->model_->jumpToTime(time);
}

bool jump(LoopSnapshot* snap, Position pos) {
  int size = snap->loops_.loop_point_size() - 1;
  int p = positionToIndex(pos, snap->segment_, size);
  snap_->loops_.mutable_loop_point(p)->set_selected(true);
  setTimeFromSegment(snap, p);
  return true;
}

bool jumpSelected(LoopSnapshot* snap, Position pos) {
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
  return true;
}

bool selectAdd(int index, int pos, bool sel, bool) { return sel || index == pos; }
bool selectOnly(int index, int pos, bool, bool) { return index == pos; }
bool toggle(int index, int pos, bool sel, bool) { return sel != (index == pos); }
bool unselect(int index, int pos, bool sel, bool) { return sel && index != pos; }

}  // namespace

void add(CallbackTable* c, int32 type, int32 position,
         SelectorFunction f, Instance* i) {
  add(c, type * Command::BANK_SIZE + position, select, i, f);
}

void add(CallbackTable* c, int32 type, int32 position,
         LoopFunction f, Instance* i) {
  add(c, type * Command::BANK_SIZE + position, loop, i, f);
}

void addRepeatedCallbacks(CallbackTable* t, Instance* i, int repeat) {
  for (int j = FIRST; j < repeat; ++j) {
    add(t, Command::JUMP_SELECTED, j, jumpSelected, i);
    add(t, Command::SELECT, j, selectAdd, i);
    add(t, Command::SELECT_ALL, j, selectAll, i);
    add(t, Command::SELECT_ONLY, j, selectOnly, i);
    add(t, Command::TOGGLE, j, toggle, i);
    add(t, Command::UNSELECT, j, unselect, i);
    add(t, Command::JUMP, j, jump, i);
  }
}

}  // namespace slow
}  // namespace rec
