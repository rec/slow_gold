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

SELECTION_OP(selectOnly0, segment == 0)
SELECTION_OP(selectOnly1, segment == 1)
SELECTION_OP(selectOnly2, segment == 2)
SELECTION_OP(selectOnly3, segment == 3)
SELECTION_OP(selectOnly4, segment == 4)
SELECTION_OP(selectOnly5, segment == 5)
SELECTION_OP(selectOnly6, segment == 6)
SELECTION_OP(selectOnly7, segment == 7)
SELECTION_OP(selectOnly8, segment == 8)
SELECTION_OP(selectOnly9, segment == 9)

SELECTION_OP(select0, selected || segment == 0)
SELECTION_OP(select1, selected || segment == 1)
SELECTION_OP(select2, selected || segment == 2)
SELECTION_OP(select3, selected || segment == 3)
SELECTION_OP(select4, selected || segment == 4)
SELECTION_OP(select5, selected || segment == 5)
SELECTION_OP(select6, selected || segment == 6)
SELECTION_OP(select7, selected || segment == 7)
SELECTION_OP(select8, selected || segment == 8)
SELECTION_OP(select9, selected || segment == 9)

SELECTION_OP(toggle0, (segment == 0) ? !selected : selected)
SELECTION_OP(toggle1, (segment == 1) ? !selected : selected)
SELECTION_OP(toggle2, (segment == 2) ? !selected : selected)
SELECTION_OP(toggle3, (segment == 3) ? !selected : selected)
SELECTION_OP(toggle4, (segment == 4) ? !selected : selected)
SELECTION_OP(toggle5, (segment == 5) ? !selected : selected)
SELECTION_OP(toggle6, (segment == 6) ? !selected : selected)
SELECTION_OP(toggle7, (segment == 7) ? !selected : selected)
SELECTION_OP(toggle8, (segment == 8) ? !selected : selected)
SELECTION_OP(toggle9, (segment == 9) ? !selected : selected)

SELECTION_OP(selectNextOnly, segment == snapshot->next_)
SELECTION_OP(selectPreviousOnly, segment == snapshot->previous_)
SELECTION_OP(selectLastOnly, segment == snapshot->last_)

SELECTION_OP(toggleWholeSongLoop,
             (snapshot->selectionCount_ == 1) || (segment == snapshot->segment_))

SELECTION_OP(unselect0, (segment != 0) && selected)
SELECTION_OP(unselect1, (segment != 1) && selected)
SELECTION_OP(unselect2, (segment != 2) && selected)
SELECTION_OP(unselect3, (segment != 3) && selected)
SELECTION_OP(unselect4, (segment != 4) && selected)
SELECTION_OP(unselect5, (segment != 5) && selected)
SELECTION_OP(unselect6, (segment != 6) && selected)
SELECTION_OP(unselect7, (segment != 7) && selected)
SELECTION_OP(unselect8, (segment != 8) && selected)
SELECTION_OP(unselect9, (segment != 9) && selected)

SELECTION_OP(selectFirst, selected || !segment)
SELECTION_OP(selectLast, selected || segment != snapshot->last_)
SELECTION_OP(selectNext, selected || segment == snapshot->next_)
SELECTION_OP(selectPrevious, selected || segment == snapshot->previous_)

JUMP_OP(jumpTo0, 0)
JUMP_OP(jumpTo1, 1)
JUMP_OP(jumpTo2, 2)
JUMP_OP(jumpTo3, 3)
JUMP_OP(jumpTo4, 4)
JUMP_OP(jumpTo5, 5)
JUMP_OP(jumpTo6, 6)
JUMP_OP(jumpTo7, 7)
JUMP_OP(jumpTo8, 8)
JUMP_OP(jumpTo9, 9)

JUMP_OP(jumpToLastSegment, snapshot->last_)
JUMP_OP(jumpToNextSegment, snapshot->next_)
JUMP_OP(jumpToPreviousSegment, snapshot->previous_)

bool clearLoops(LoopSnapshot* s) {
  s->loops_.Clear();
  s->loops_.add_loop_point();
  return true;
}

typedef LoopSnapshot::Map Map;

const Map& getLoopMap() {
  using rec::command::Command;
  static const Map::value_type values[] = {
    make_pair(Command::CLEAR_LOOPS, &clearLoops),
    make_pair(Command::DESELECT_ALL, &deselectAll),
    make_pair(Command::INVERT_LOOP_SELECTION, &invertLoopSelection),

    make_pair(Command::JUMP_TO_0, &jumpTo0),
    make_pair(Command::JUMP_TO_1, &jumpTo1),
    make_pair(Command::JUMP_TO_2, &jumpTo2),
    make_pair(Command::JUMP_TO_3, &jumpTo3),
    make_pair(Command::JUMP_TO_4, &jumpTo4),
    make_pair(Command::JUMP_TO_5, &jumpTo5),
    make_pair(Command::JUMP_TO_6, &jumpTo6),
    make_pair(Command::JUMP_TO_7, &jumpTo7),
    make_pair(Command::JUMP_TO_8, &jumpTo8),
    make_pair(Command::JUMP_TO_9, &jumpTo9),

    make_pair(Command::JUMP_TO_PREVIOUS_SEGMENT, jumpToPreviousSegment),
    make_pair(Command::JUMP_TO_NEXT_SEGMENT, jumpToNextSegment),
    make_pair(Command::JUMP_TO_LAST_SEGMENT, &jumpToLastSegment),

    make_pair(Command::SELECT_ALL, &selectAll),

    make_pair(Command::SELECT_ONLY_0, &selectOnly0),
    make_pair(Command::SELECT_ONLY_1, &selectOnly1),
    make_pair(Command::SELECT_ONLY_2, &selectOnly2),
    make_pair(Command::SELECT_ONLY_3, &selectOnly3),
    make_pair(Command::SELECT_ONLY_4, &selectOnly4),
    make_pair(Command::SELECT_ONLY_5, &selectOnly5),
    make_pair(Command::SELECT_ONLY_6, &selectOnly6),
    make_pair(Command::SELECT_ONLY_7, &selectOnly7),
    make_pair(Command::SELECT_ONLY_8, &selectOnly8),
    make_pair(Command::SELECT_ONLY_9, &selectOnly9),

    make_pair(Command::SELECT_0, &select0),
    make_pair(Command::SELECT_1, &select1),
    make_pair(Command::SELECT_2, &select2),
    make_pair(Command::SELECT_3, &select3),
    make_pair(Command::SELECT_4, &select4),
    make_pair(Command::SELECT_5, &select5),
    make_pair(Command::SELECT_6, &select6),
    make_pair(Command::SELECT_7, &select7),
    make_pair(Command::SELECT_8, &select8),
    make_pair(Command::SELECT_9, &select9),

    make_pair(Command::SELECT_NEXT_SEGMENT_ONLY, &selectNextOnly),
    make_pair(Command::SELECT_PREVIOUS_SEGMENT_ONLY, &selectPreviousOnly),
    make_pair(Command::SELECT_LAST_SEGMENT_ONLY, &selectLastOnly),

    make_pair(Command::TOGGLE_0, &toggle0),
    make_pair(Command::TOGGLE_1, &toggle1),
    make_pair(Command::TOGGLE_2, &toggle2),
    make_pair(Command::TOGGLE_3, &toggle3),
    make_pair(Command::TOGGLE_4, &toggle4),
    make_pair(Command::TOGGLE_5, &toggle5),
    make_pair(Command::TOGGLE_6, &toggle6),
    make_pair(Command::TOGGLE_7, &toggle7),
    make_pair(Command::TOGGLE_8, &toggle8),
    make_pair(Command::TOGGLE_9, &toggle9),

    make_pair(Command::TOGGLE_WHOLE_SONG_LOOP, &toggleWholeSongLoop),

    make_pair(Command::UNSELECT_0, &unselect0),
    make_pair(Command::UNSELECT_1, &unselect1),
    make_pair(Command::UNSELECT_2, &unselect2),
    make_pair(Command::UNSELECT_3, &unselect3),
    make_pair(Command::UNSELECT_4, &unselect4),
    make_pair(Command::UNSELECT_5, &unselect5),
    make_pair(Command::UNSELECT_6, &unselect6),
    make_pair(Command::UNSELECT_7, &unselect7),
    make_pair(Command::UNSELECT_8, &unselect8),
    make_pair(Command::UNSELECT_9, &unselect9),
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
