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

void addSelectionCallbacks(command::CommandRecordTable* t) {
	static const CommandIDEncoder noPos(CommandIDEncoder::CURRENT);
  addCallbackNoInstance(t, Command::DESELECT_ALL, selectNoInstance, deselectAll, noPos);
  addCallbackNoInstance(t, Command::SELECT_ALL, selectNoInstance, selectAll, noPos);
  addCallbackNoInstance(t, Command::INVERT_LOOP_SELECTION, selectNoInstance, invertLoopSelection,
              noPos);
  addCallbackNoInstance(t, Command::TOGGLE_WHOLE_SONG_LOOP, selectNoInstance, toggleWholeSongLoop,
              noPos);
}

}  // namespace slow
}  // namespace rec
