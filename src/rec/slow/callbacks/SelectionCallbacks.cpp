#include "rec/slow/callbacks/SelectionCallbacks.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/CurrentTime.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

void selectX(SelectorFunction selector, CommandIDEncoder pos) {
  Instance* instance = Instance::getInstance();
  LoopSnapshot snap(instance);
  LoopPointList* loops = snap.loops_;
  int segment = audio::getSegment(*loops, snap.instance_->time());
  int size = loops->loop_point_size();
  int p = pos.toIndex(segment, size);

  bool multipleSelections = (audio::getSelectionCount(*snap.loops_) > 1);

  for (int i = 0; i < size; ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected(selector(i, p, lp->selected(), multipleSelections));
  }
  instance->setProto(snap.viewport_);
}

template <typename Function, typename X, typename Y>
void addCallbackX(CommandRecordTable* c, CommandID id, Function f, X x, Y y) {
  addCallback(c, id, thread::functionCallback(f, x, y));
}

bool selectAll(int, int, bool, bool) { return true; }
bool deselectAll(int, int, bool, bool) { return false; }
bool invertLoopSelection(int, int, bool sel, bool) { return !sel; }
bool toggleWholeSongLoop(int i, int p, bool, bool al) {
  return !al || i == p;
}

}  // namespace

void addSelectionCallbacks(command::CommandRecordTable* t) {
	static const CommandIDEncoder noPos(CommandIDEncoder::CURRENT);
  addCallbackX(t, Command::DESELECT_ALL, selectX, deselectAll, noPos);
  addCallbackX(t, Command::SELECT_ALL, selectX, selectAll, noPos);
  addCallbackX(t, Command::INVERT_LOOP_SELECTION, selectX, invertLoopSelection, noPos);
  addCallbackX(t, Command::TOGGLE_WHOLE_SONG_LOOP, selectX, toggleWholeSongLoop, noPos);
}

}  // namespace slow
}  // namespace rec
