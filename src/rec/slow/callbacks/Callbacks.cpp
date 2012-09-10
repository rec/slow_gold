#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/slow/callbacks/SelectionCallbacks.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

using command::CommandRecordTable;

void addSlowCallbacks(CommandRecordTable* table, int repeat) {
  addGlobalCallbacks(table);
  addInstanceCallbacks(table);
  addSelectionCallbacks(table);
  addRepeatedCallbacks(table, repeat);
}

}  // namespace slow
}  // namespace rec
