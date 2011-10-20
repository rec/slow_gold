#include "rec/slow/callbacks/SelectionCallbacks.h"
#include "rec/slow/callbacks/CallbackUtils.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

bool selectAll(int, int, bool, bool) { return true; }
bool deselectAll(int, int, bool, bool) { return false; }
bool invertLoopSelection(int, int, bool sel, bool) { return !sel; }
bool toggleWholeSongLoop(int i, int p, bool, bool al) { return !al || i == p; }

void addSelectionCallbacks(CallbackTable* t, Instance* i) {
	static const Position noPos(Position::CURRENT);
  add(t, Command::DESELECT_ALL, select, i, deselectAll, noPos);
  add(t, Command::SELECT_ALL, select, i, selectAll, noPos);
  add(t, Command::INVERT_LOOP_SELECTION, select, i, invertLoopSelection, noPos);
  add(t, Command::TOGGLE_WHOLE_SONG_LOOP, select, i, toggleWholeSongLoop, noPos);
}

}  // namespace slow
}  // namespace rec
