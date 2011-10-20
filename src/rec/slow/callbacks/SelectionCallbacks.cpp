#include "rec/slow/callbacks/SelectionCallbacks.h"
#include "rec/slow/callbacks/Callbacks.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

bool selectAll(int, int, bool, bool) { return true; }
bool deselectAll(int, int, bool, bool) { return false; }
bool invertLoopSelection(int, int, bool sel, bool) { return !sel; }
bool toggleWholeSongLoop(int i, int p, bool, bool al) { return !al || i == p; }

void addSelectionCallbacks(CallbackTable* t, Instance* i) {
  add(t, Command::DESELECT_ALL, select, i, deselectAll, CURRENT);
  add(t, Command::SELECT_ALL, select, i, selectAll, CURRENT);
  add(t, Command::INVERT_LOOP_SELECTION, select, i, invertLoopSelection, CURRENT);
  add(t, Command::TOGGLE_WHOLE_SONG_LOOP, select, i, toggleWholeSongLoop, CURRENT);
}

}  // namespace slow
}  // namespace rec
