#include <map>

#include "rec/slow/LoopCommands.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Model.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/util/Math.h"
#include "rec/base/Arraysize.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace applier {

// We repeat "first" to make it easy to have uniform menus.
enum Position { FIRST = -5, PREVIOUS = -4, CURRENT = -3, NEXT = -2, LAST = -1, ZERO = 0 };

typedef bool (*SelectorFunction)(int index, int pos, bool selected, bool all);
typedef bool (*LoopFunction)(LoopSnapshot*, Position);
typedef std::pair<SelectorFunction, LoopFunction> CommandFunction;

typedef std::map<Command::Type, CommandFunction> CommandMap;

int getPosition(Position pos, int segment, int size) {
  int p =
    (pos == FIRST) ? 0 :
    (pos == PREVIOUS) ? segment - 1 :
    (pos == CURRENT) ? segment :
    (pos == NEXT) ? segment + 1 :
    (pos == LAST) ? size - 1 :
    static_cast<int>(pos);
  return mod(p, size);
}

bool select(SelectorFunction f, LoopSnapshot* snap, Position pos) {
  int size = snap->loops_.loop_point_size();
  int p = getPosition(pos, snap->segment_, size);

  LoopPointList* loops = &snap->loops_;
  bool allSelected = (snap->selectionCount_ == size);

  for (int i = 0; i < loops->loop_point_size(); ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(f(i, p, lp->selected(), allSelected));
  }
  return true;
}

bool executeCommand(Instance* instance, Command::Type c, const CommandMap& map) {
  Command::Type command = c;
  Position pos = CURRENT;
  if (command >= Command::BANK_START || command < Command::BANK_END) {
    command = static_cast<Command::Type>(Command::BANK_SIZE *
                                         (command / Command::BANK_SIZE));
    pos = static_cast<Position>(command - c - PREVIOUS);
  }

  CommandMap::const_iterator i = map.find(command);
  if (i == map.end())
    return false;

  LoopSnapshot s(instance);
  bool success = select(i->second.first, &s, pos) && i->second.second(&s, pos);
  if (success)
    persist::set(s.loops_, instance->model_->file());
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
  int p = getPosition(pos, snap->segment_, snap->loops_.loop_point_size());
  setTimeFromSegment(snap, p);
  return true;
}

bool jumpSelected(LoopSnapshot* snap, Position pos) {
  vector<int> selected;
  size_t s = -100;
  for (int i = 0; i < snap->loops_.loop_point_size(); ++i) {
    if (!snap->selectionCount_ || snap->loops_.loop_point(i).selected()) {
      if (i == snap->segment_) {
        DCHECK_EQ(s, -1);
        s = selected.size();
      }
      selected.push_back(i);
    }
  }

  DCHECK_NE(s, -100);
  setTimeFromSegment(snap, selected[getPosition(pos, s, selected.size())]);
  return true;
}

bool clearLoops(LoopSnapshot* s, Position pos) {
  s->loops_.Clear();
  s->loops_.add_loop_point();
  return true;
}

CommandFunction make(SelectorFunction f) { return make_pair(f, noFunction); }
CommandFunction make(LoopFunction f) { return make_pair(noSelector, f); }

CommandMap makeMap() {
  CommandMap m;
  m[Command::SELECT_ALL] = make(selectAll);
  m[Command::DESELECT_ALL] = make(deselectAll);
  m[Command::INVERT_LOOP_SELECTION] = make(invertLoopSelection);
  m[Command::CLEAR_LOOPS] = make(clearLoops);
  m[Command::SELECT] = make(selectAdd);
  m[Command::SELECT_ONLY] = make(selectOnly);
  m[Command::TOGGLE] = make(toggle);
  m[Command::UNSELECT] = make(unselect);
  m[Command::JUMP] = std::make_pair(selectAdd, jump);
  m[Command::JUMP_SELECTED] = make(jumpSelected);
  m[Command::TOGGLE_WHOLE_SONG_LOOP] = make(toggleWholeSongLoop);
  m[Command::CLEAR_LOOPS] = make(clearLoops);

  return m;
}


}  // namespace applier

bool executeLoopCommand(Instance* instance, Command::Type command) {
  static applier::CommandMap map = applier::makeMap();
  return applier::executeCommand(instance, command, map);
}

}  // namespace slow
}  // namespace rec
