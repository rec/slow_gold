#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/BufferFiller.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

int getSegment(const LoopSnapshot& snap) {
  return audio::getSegment(snap.loops_, snap.instance_->time());
}

void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
  RealTime time = snapshot->loops_.loop_point(segment).time();
  snapshot->instance_->currentTime_->jumpToTime(time);
}

void jump(LoopSnapshot* snap, Position pos) {
  int size = snap->loops_.loop_point_size() - 1;
  int p = pos.toIndex(getSegment(*snap), size);
  snap->loops_.mutable_loop_point(p)->set_selected(true);
  setTimeFromSegment(snap, p);
}

void jumpSelected(LoopSnapshot* snap, Position pos) {
  vector<int> selected;
  size_t s;
  bool found = false;
  const LoopPointList& loops = snap->loops_;
  for (int i = 0; i < loops.loop_point_size() - 1; ++i) {
    if (!audio::getSelectionCount(loops) || loops.loop_point(i).selected()) {
      if (i == getSegment(*snap)) {
        DCHECK(!found);
        s = selected.size();
        found = true;
      }
      selected.push_back(i);
    }
  }

  DCHECK(found);
  setTimeFromSegment(snap, selected[pos.toIndex(s, selected.size())]);
}

bool selectAdd(int index, int pos, bool sel, bool) { return sel || index == pos; }
bool selectOnly(int index, int pos, bool, bool) { return index == pos; }
bool toggle(int index, int pos, bool sel, bool) { return sel != (index == pos); }
bool unselect(int index, int pos, bool sel, bool) { return sel && index != pos; }

void add(CommandRecordTable* c, int32 type, Position position,
         SelectorFunction f, Instance* i) {
  add(c, position.toCommandID(type), select, i, f, position);
}

void add(CommandRecordTable* c, int32 type, Position position,
         LoopSnapshotFunction f, Instance* i) {
  add(c, position.toCommandID(type), loop, i, f, position);
}

static const int RECENT_MENU_REPEATS = 65;

void loadRecentFile(Instance* instance, int i) {
  gui::RecentFiles rf = data::get<gui::RecentFiles>();
  if (i < 0 || i >= rf.file_size()) {
    LOG(ERROR) << "Can't load recent, i=" << i << ", size=" << rf.file_size();
    return;
  }

  (*instance->currentFile_)(rf.file(i).file());
}

}  // namespace

void addRepeatedCallbacks(CommandRecordTable* t, Instance* i, int repeat) {
  for (int j = Position::FIRST; j < repeat; ++j) {
  	Position pos(j);
    add(t, Command::SELECT, pos, selectAdd, i);
    add(t, Command::SELECT_ONLY, pos, selectOnly, i);
    add(t, Command::TOGGLE_SELECTION, pos, toggle, i);
    add(t, Command::UNSELECT, pos, unselect, i);

    add(t, Command::JUMP_SELECTED, pos, jumpSelected, i);
    add(t, Command::JUMP, pos, jump, i);
  }

  for (int j = 0; j < RECENT_MENU_REPEATS; ++j) {
    CommandID id = Position::toCommandID(j, Command::RECENT_FILES);
    add(t, id, loadRecentFile, i, j);
  }
}

}  // namespace slow
}  // namespace rec
