#include "rec/slow/LoopsTimeAndSelection.h"

#include "rec/audio/source/Player.h"

namespace rec {
namespace slow {

LoopsTimeAndSelection::LoopsTimeAndSelection(Instance* i)
  : HasInstance(i),
    loops_(model()->loopPointList()),
    time_(player()->getNextReadPosition()),
    segment_(getContainingSegment()),
    selection_(model()->timeSelection()) {
}

void LoopsTimeAndSelection::toggleWholeSongLoop() {
  int size = loops_.loop_point_size();
  if (size == 1) {
    PlatformUtilities::beep();
    return;
  }

  int selectionCount = 0;
  for (int i = 0; i < size; ++i) {
    if (loops_.loop_point(i).selected())
      selectionCount++;
  }

  bool selectAll = (selectionCount == 1);
  for (int i = 0; i < size; ++i)
    loops_.mutable_loop_point(i)->set_selected(selectAll || i == segment_);
  setData();
}

void LoopsTimeAndSelection::jumpToNextLoopPoint() {
}

void LoopsTimeAndSelection::jumpToPreviousLoopPoint() {
}

void LoopsTimeAndSelection::jumpToStart() {
}

void LoopsTimeAndSelection::jumpToNextLoopPointInSelection() {
}

void LoopsTimeAndSelection::jumpToPreviousLoopPointInSelection() {
}

void LoopsTimeAndSelection::jumpToStartOfSelection( ) {
}

void LoopsTimeAndSelection::setData() {
  persist::set(loops_, instance_->model_->file());
}

int LoopsTimeAndSelection::getContainingSegment() const {
  for (int i = 1; ; ++i) {
    if (i >= loops_.loop_point_size() || time_ < loops_.loop_point(i).time())
      return i - 1;
  }
}

}  // namespace slow
}  // namespace rec
