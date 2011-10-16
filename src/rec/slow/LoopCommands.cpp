#include <map>

#include "rec/slow/LoopCommands.h"
#include "rec/base/Arraysize.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/slow/Model.h"
#include "rec/slow/Position.h"
#include "rec/util/Math.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace applier {

typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);
typedef bool (*LoopFunction)(LoopSnapshot*, Position);
typedef std::pair<SelectorFunction, LoopFunction> CommandFunction;

typedef std::map<Command::Type, CommandFunction> CommandMap;

bool select(SelectorFunction f, LoopSnapshot* snap, Position pos) {
  LoopPointList* loops = &snap->loops_;
  int size = loops->loop_point_size() - 1;
  int p = positionToIndex(pos, snap->segment_, size);

  bool allSelected = (snap->selectionCount_ == size);

  for (int i = 0; i < size; ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(f(i, p, lp->selected(), allSelected));
  }
  return true;
}

bool executeCommand(Instance* instance, Command::Type c, const CommandMap& map) {
  Command::Type command = getCommandBase(c);
  CommandMap::const_iterator i = map.find(command);
  if (i == map.end())
    return false;

  LoopSnapshot s(instance);
  Position pos = getPosition(c);
  bool success = select(i->second.first, &s, pos) && i->second.second(&s, pos);
  if (success)
    data::set(s.loops_, instance->model_->file());
  else
    PlatformUtilities::beep();

  return success;
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

void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
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

bool clearLoops(LoopSnapshot* s, Position pos) {
  s->loops_.Clear();
  s->loops_.add_loop_point();
  return true;
}

CommandFunction make(SelectorFunction f) { return make_pair(f, &noFunction); }
CommandFunction make(LoopFunction f) { return make_pair(&noSelector, f); }

CommandMap makeMap() {
  CommandMap m;
  m[Command::CLEAR_LOOPS] = make(clearLoops);
  m[Command::DESELECT_ALL] = make(deselectAll);
  m[Command::INVERT_LOOP_SELECTION] = make(invertLoopSelection);
  m[Command::JUMP] = std::make_pair(&selectAdd, &jump);
  m[Command::JUMP_SELECTED] = make(jumpSelected);
  m[Command::SELECT] = make(selectAdd);
  m[Command::SELECT_ALL] = make(selectAll);
  m[Command::SELECT_ONLY] = make(selectOnly);
  m[Command::TOGGLE] = make(toggle);
  m[Command::TOGGLE_WHOLE_SONG_LOOP] = make(toggleWholeSongLoop);
  m[Command::UNSELECT] = make(unselect);

  return m;
}


}  // namespace applier

bool executeLoopCommand(Instance* instance, Command::Type command) {
  static applier::CommandMap map = applier::makeMap();
  return applier::executeCommand(instance, command, map);
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
