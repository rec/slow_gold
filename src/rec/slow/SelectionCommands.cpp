#include <map>

#include "rec/slow/LoopCommands.h"
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

bool jump(LoopSnapshot* snap, Position pos) {
  int size = snap->loops_.loop_point_size() - 1;
  int p = positionToIndex(pos, snap->segment_, size);
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

void addLoopsToCommandTable(CallbackTable* t, Instance* i) {
  using thread::functionCallback;
  Position noPos;

  (*t)[Command::CLEAR_LOOPS] = functionCallback(loop, i, clearLoops, noPos);



bool select(SelectorFunction selector, Instance* instance, Position pos) {
  LoopSnapshot s(instance);
  LoopPointList* loops = &snap->loops_;
  int size = loops->loop_point_size() - 1;
  int p = positionToIndex(pos, snap->segment_, size);

  bool allSelected = (snap->selectionCount_ == size);

  for (int i = 0; i < size; ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(selector(i, p, lp->selected(), allSelected));
  }
  data::set(s.loops_, instance->model_->file());
  return true;
}

}  // namespace

typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);

void addLoopsToCommandTable(CallbackTable* t, Instance* i) {
  using thread::functionCallback;
  Position noPos;

  (*t)[Command::CLEAR_LOOPS] = functionCallback(loop, clearLoops, noPos);
  m[Command::DESELECT_ALL] = make(deselectAll);
  m[Command::INVERT_LOOP_SELECTION] = make(invertLoopSelection);
  m[Command::JUMP_SELECTED] = make(jumpSelected);
  m[Command::SELECT] = make(selectAdd);
  m[Command::SELECT_ALL] = make(selectAll);
  m[Command::SELECT_ONLY] = make(selectOnly);
  m[Command::TOGGLE] = make(toggle);
  m[Command::TOGGLE_WHOLE_SONG_LOOP] = make(toggleWholeSongLoop);
  m[Command::UNSELECT] = make(unselect);

  m[Command::JUMP] = std::make_pair(&selectAdd, &jump);

}

typedef std::pair<SelectorFunction, LoopFunction> CommandFunction;

typedef std::map<int, CommandFunction> CommandMap;

bool execute(Instance* instance, Position pos,
             const CommandFunction& cf) {
  LoopSnapshot s(instance);
  bool success = select(cf.first, &s, pos) && cf.second(&s, pos);
  if (success)
    data::set(s.loops_, instance->model_->file());
  else
    beep();

  return success;
}


bool executeCommand(Instance* i, const Command& c, const CommandMap& map) {
  CommandMap::const_iterator i = map.find(command);
  return (i != map.end()) && exec(i, getPosition(getCommandBase(c)), i->second);
}

bool selectAll(int, int, bool, bool) { return true; }
bool deselectAll(int, int, bool, bool) { return false; }
bool invertLoopSelection(int, int, bool sel, bool) { return !sel; }
bool noSelector(int, int, bool sel, bool) { return sel; }
bool toggleWholeSongLoop(int i, int p, bool, bool al) { return !al || i == p; }

bool selectAdd(int index, int pos, bool sel, bool) { return sel || index == pos; }
bool selectOnly(int index, int pos, bool, bool) { return index == pos; }
bool toggle(int index, int pos, bool sel, bool) { return sel != (index == pos); }
bool unselect(int index, int pos, bool sel, bool) { return sel && index != pos; }

bool noFunction(LoopSnapshot*, Position) { return true; }

CommandFunction make(SelectorFunction f) { return make_pair(f, &noFunction); }
CommandFunction make(LoopFunction f) { return make_pair(&noSelector, f); }

CommandMap makeMap() {
  CommandMap m;
  m[Command::CLEAR_LOOPS] = make(clearLoops);
  m[Command::DESELECT_ALL] = make(deselectAll);
  m[Command::INVERT_LOOP_SELECTION] = make(invertLoopSelection);
  m[Command::JUMP_SELECTED] = make(jumpSelected);
  m[Command::SELECT] = make(selectAdd);
  m[Command::SELECT_ALL] = make(selectAll);
  m[Command::SELECT_ONLY] = make(selectOnly);
  m[Command::TOGGLE] = make(toggle);
  m[Command::TOGGLE_WHOLE_SONG_LOOP] = make(toggleWholeSongLoop);
  m[Command::UNSELECT] = make(unselect);

  m[Command::JUMP] = std::make_pair(&selectAdd, &jump);

  return m;
}

}  // namespace

bool executeLoopCommand(Instance* instance, const Command& command) {
  static CommandMap map = makeMap();
  return executeCommand(instance, command, map);
}

void toggleSelectionSegment(const VirtualFile& file, RealTime time) {
  LoopPointList loops(data::get<LoopPointList>(file));

  int i = 0, size = loops.loop_point_size();
  for (; i < size && loops.loop_point(i).time() <= time; ++i);
  LoopPoint* lp = loops.mutable_loop_point(i - 1);
  lp->set_selected(!lp->selected());
  data::set(loops, file);
}

}  // namespace slow
}  // namespace rec
