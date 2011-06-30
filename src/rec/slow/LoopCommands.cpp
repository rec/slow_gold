#include "rec/slow/LoopCommands.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/base/Arraysize.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

bool clearLoops(LoopSnapshot* s) {
  s->loops_.Clear();
  return true;
}

template <typename Operator>
bool applySelected(Operator op, LoopSnapshot* s) {
  LoopPointList* loops = &s->loops_;
  for (int i = 0; i < loops->loop_point_size(); ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected((*op)(lp->selected(), i, s));
  }
  return true;
}

#define SELECTION_OP(NAME, RESULT) \
  bool NAME ## Op(bool selected, int segment, LoopSnapshot* snapshot) { \
    return RESULT;                                                      \
  }                                                                     \
  bool NAME(LoopSnapshot* s) { return applySelected(NAME ## Op, s); }


SELECTION_OP(selectAll, true)
SELECTION_OP(deselectAll, false)
SELECTION_OP(invertLoopSelection, !selected)
SELECTION_OP(selectFirstOnly, !segment)
SELECTION_OP(selectLastOnly, segment != snapshot->loopSize_)
SELECTION_OP(selectNextOnly, segment == snapshot->next_)
SELECTION_OP(selectPreviousOnly, segment == snapshot->next_)
SELECTION_OP(toggleWholeSongLoop,
             (snapshot->selectionCount_ == 1) || (segment == snapshot->segment_))

bool contractFromNextLoopPoint(LoopSnapshot* s) {
  return false;
}

bool contractFromPreviousLoopPoint(LoopSnapshot* s) {
  return false;
}

bool extendToNextLoopPoint(LoopSnapshot* s) {
  return false;
}

bool extendToPreviousLoopPoint(LoopSnapshot* s) {
  return false;
}

bool jumpToEndAndSelect(LoopSnapshot* s) {
  return false;
}

bool jumpToNextLoopPointAndSelect(LoopSnapshot* s) {
  return false;
}

bool jumpToNextLoopPointInSelection(LoopSnapshot* s) {
  return false;
}

bool jumpToPreviousLoopPointAndSelect(LoopSnapshot* s) {
  return false;
}

bool jumpToPreviousLoopPointInSelection(LoopSnapshot* s) {
  return false;
}

bool jumpToStartAndSelect(LoopSnapshot* s) {
  return false;
}

bool jumpToStartOfSelection(LoopSnapshot* s) {
  return false;
}

typedef LoopSnapshot::Map Map;

const Map& getLoopMap() {
  static const Map::value_type values[] = {
    make_pair(Command::CLEAR_LOOPS,
              &clearLoops),
    make_pair(Command::CONTRACT_FROM_NEXT_LOOP_POINT,
              &contractFromNextLoopPoint),
    make_pair(Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT,
              &contractFromPreviousLoopPoint),
    make_pair(Command::DESELECT_ALL,
              &deselectAll),
    make_pair(Command::EXTEND_TO_NEXT_LOOP_POINT,
              &extendToNextLoopPoint),
    make_pair(Command::EXTEND_TO_PREVIOUS_LOOP_POINT,
              &extendToPreviousLoopPoint),
    make_pair(Command::INVERT_LOOP_SELECTION,
              &invertLoopSelection),
    make_pair(Command::JUMP_TO_END_AND_SELECT,
              &jumpToEndAndSelect),
    make_pair(Command::JUMP_TO_NEXT_LOOP_POINT_AND_SELECT,
              jumpToNextLoopPointAndSelect),
    make_pair(Command::JUMP_TO_NEXT_LOOP_POINT_IN_SELECTION,
              &jumpToNextLoopPointInSelection),
    make_pair(Command::JUMP_TO_PREVIOUS_LOOP_POINT_AND_SELECT,
              &jumpToPreviousLoopPointAndSelect),
    make_pair(Command::JUMP_TO_PREVIOUS_LOOP_POINT_IN_SELECTION,
              &jumpToPreviousLoopPointInSelection),
    make_pair(Command::JUMP_TO_START_AND_SELECT,
              &jumpToStartAndSelect),
    make_pair(Command::JUMP_TO_START_OF_SELECTION,
              &jumpToStartOfSelection),
    make_pair(Command::SELECT_ALL,
              &selectAll),
    make_pair(Command::SELECT_FIRST_ONLY,
              &selectFirstOnly),
    make_pair(Command::SELECT_LAST_ONLY,
              &selectLastOnly),
    make_pair(Command::SELECT_NEXT_ONLY,
              &selectNextOnly),
    make_pair(Command::SELECT_PREVIOUS_ONLY,
              &selectPreviousOnly),
    make_pair(Command::TOGGLE_WHOLE_SONG_LOOP,
              &toggleWholeSongLoop),
  };

  static const Map map(values, values + arraysize(values));
  return map;
}

}  // namespace

bool executeLoopCommand(Command::Type command, Instance* instance) {
  return LoopSnapshot(instance).execute(command, getLoopMap());
}

}  // namespace slow
}  // namespace rec
