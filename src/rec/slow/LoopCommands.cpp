#include "rec/slow/LoopCommands.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Model.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/base/Arraysize.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

template <typename Operator>
bool applySelected(Operator op, LoopSnapshot* s) {
  LoopPointList* loops = &s->loops_;
  for (int i = 0; i < loops->loop_point_size(); ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected((*op)(lp->selected(), i, s));
  }
  return true;
}


#define _OP(NAME, RESULT)                                               \
  bool NAME ## Op(bool selected, int segment, LoopSnapshot* snapshot) { \
    return RESULT;                                                      \
  }

#define SELECTION_OP(NAME, RESULT)                                      \
  _OP(NAME, RESULT)                                                     \
                                                                        \
  bool NAME(LoopSnapshot* s) { return applySelected(NAME ## Op, s); }

#define JUMP_SELECT_OP(NAME, RESULT, JUMP_SEGMENT)                      \
  _OP(NAME, RESULT)                                                     \
                                                                        \
  bool NAME(LoopSnapshot* snapshot) {                                   \
    bool result = applySelected(NAME ## Op, snapshot);                  \
    RealTime time = snapshot->loops_.loop_point(JUMP_SEGMENT).time();   \
    snapshot->instance_->model_->jumpToTime(time);                      \
    return result;                                                      \
  }

#define JUMP_OP(NAME, JUMP_SEGMENT)                                     \
  JUMP_SELECT_OP(NAME, selected || segment == JUMP_SEGMENT, JUMP_SEGMENT)


SELECTION_OP(selectAll, true)
SELECTION_OP(deselectAll, false)
SELECTION_OP(invertLoopSelection, !selected)
SELECTION_OP(selectFirstOnly, !segment)
SELECTION_OP(selectLastOnly, segment == snapshot->last_)
SELECTION_OP(selectNextOnly, segment == snapshot->next_)
SELECTION_OP(selectPreviousOnly, segment == snapshot->previous_)
SELECTION_OP(toggleWholeSongLoop,
             (snapshot->selectionCount_ == 1) || (segment == snapshot->segment_))

SELECTION_OP(selectFirst, selected || !segment)
SELECTION_OP(selectLast, selected || segment != snapshot->last_)
SELECTION_OP(selectNext, selected || segment == snapshot->next_)
SELECTION_OP(selectPrevious, selected || segment == snapshot->previous_)

JUMP_OP(jumpToFirstLoopPointAndSelect, 0)
JUMP_OP(jumpToLastLoopPointAndSelect, snapshot->last_)
JUMP_OP(jumpToNextLoopPointAndSelect, snapshot->next_)
JUMP_OP(jumpToPreviousLoopPointAndSelect, snapshot->previous_)

bool clearLoops(LoopSnapshot* s) {
  s->loops_.Clear();
  return true;
}

typedef LoopSnapshot::Map Map;

const Map& getLoopMap() {
  using rec::command::Command;
  static const Map::value_type values[] = {
    make_pair(Command::CLEAR_LOOPS,
              &clearLoops),
    make_pair(Command::DESELECT_ALL,
              &deselectAll),
    make_pair(Command::INVERT_LOOP_SELECTION,
              &invertLoopSelection),
    make_pair(Command::JUMP_TO_NEXT_SEGMENT,
              jumpToLastLoopPointAndSelect),
    make_pair(Command::JUMP_TO_PREVIOUS_SEGMENT,
              jumpToLastLoopPointAndSelect),
    make_pair(Command::JUMP_TO_LAST_SEGMENT,
              &jumpToLastLoopPointAndSelect),
    make_pair(Command::SELECT_ALL,
              &selectAll),
    make_pair(Command::SELECT_ONLY_0,
              &selectFirstOnly),
    make_pair(Command::SELECT_NEXT_SEGMENT_ONLY,
              &selectNextOnly),
    make_pair(Command::SELECT_PREVIOUS_SEGMENT_ONLY,
              &selectPreviousOnly),
    make_pair(Command::SELECT_LAST_SEGMENT_ONLY,
              &selectLastOnly),
    make_pair(Command::TOGGLE_WHOLE_SONG_LOOP,
              &toggleWholeSongLoop),
  };

  static const Map map(values, values + arraysize(values));
  return map;
}

}  // namespace

bool executeLoopCommand(Instance* instance, Command command) {
  return LoopSnapshot(instance).execute(command, getLoopMap());
}

}  // namespace slow
}  // namespace rec
