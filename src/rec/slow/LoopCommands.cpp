#include "rec/slow/LoopCommands.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/base/Arraysize.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

typedef LoopSnapshot::Map Map;

int getContainingSegment(const LoopSnapshot& snapshot) {
  const LoopPointList& loops = snapshot.loops_;
  for (int i = 1; ; ++i) {
    if (i >= loops.loop_point_size() || snapshot.time_ < loops.loop_point(i).time())
      return i - 1;
  }
}

int getSelectionCount(const LoopPointList& loops) {
  int c = 0, size = loops.loop_point_size();
  for (int i = 0; i < size; ++i) {
    if (loops.loop_point(i).selected())
      c++;
  }
  return c ? c : size;
}

bool toggleWholeSongLoop(LoopSnapshot* snapshot) {
  LoopPointList& loops = snapshot->loops_;
  int size = loops.loop_point_size();
  if (size == 1)
    return false;

  int segment = getContainingSegment(*snapshot);
  bool selectAll = (getSelectionCount(snapshot->loops_) == 1);
  for (int i = 0; i < size; ++i)
    loops.mutable_loop_point(i)->set_selected(selectAll || i == segment);

  return true;
}

bool clearLoops(LoopSnapshot* snapshot) {
  return false;
}

bool contractFromNextLoopPoint(LoopSnapshot* snapshot) {
  return false;
}

bool contractFromPreviousLoopPoint(LoopSnapshot* snapshot) {
  return false;
}

bool extendToNextLoopPoint(LoopSnapshot* snapshot) {
  return false;
}

bool extendToPreviousLoopPoint(LoopSnapshot* snapshot) {
  return false;
}

bool invertLoopSelection(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToEndAndSelect(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToNextLoopPointAndSelect(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToNextLoopPointInSelection(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToPreviousLoopPointAndSelect(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToPreviousLoopPointInSelection(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToStartAndSelect(LoopSnapshot* snapshot) {
  return false;
}

bool jumpToStartOfSelection(LoopSnapshot* snapshot) {
  return false;
}

bool selectFirstOnly(LoopSnapshot* snapshot) {
  return false;
}

bool selectLastOnly(LoopSnapshot* snapshot) {
  return false;
}

bool selectNextOnly(LoopSnapshot* snapshot) {
  return false;
}

bool selectPreviousOnly(LoopSnapshot* snapshot) {
  return false;
}

const Map& getLoopMap() {
  static const Map::value_type values[] = {
    make_pair(Command::CLEAR_LOOPS,
              &clearLoops),
    make_pair(Command::CONTRACT_FROM_NEXT_LOOP_POINT,
              &contractFromNextLoopPoint),
    make_pair(Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT,
              &contractFromPreviousLoopPoint),
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
