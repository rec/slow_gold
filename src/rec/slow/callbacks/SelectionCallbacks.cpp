#include "rec/slow/callbacks/SelectionCallbacks.h"
#include "rec/slow/callbacks/CallbackUtils.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

bool selectAll(int, int, bool, bool) { return true; }
bool deselectAll(int, int, bool, bool) { return false; }
bool invertLoopSelection(int, int, bool sel, bool) { return !sel; }
bool toggleWholeSongLoop(int i, int p, bool, bool al) {
  return !al || i == p;
}

}  // namespace

void addSelectionCallbacks(command::CommandRecordTable* t, Instance* i) {
	static const CommandIDEncoder noPos(CommandIDEncoder::CURRENT);
  addCallback(t, Command::DESELECT_ALL, select, i, deselectAll, noPos);
  addCallback(t, Command::SELECT_ALL, select, i, selectAll, noPos);
  addCallback(t, Command::INVERT_LOOP_SELECTION, select, i, invertLoopSelection,
              noPos);
  addCallback(t, Command::TOGGLE_WHOLE_SONG_LOOP, select, i, toggleWholeSongLoop,
              noPos);
}

}  // namespace slow
}  // namespace rec
