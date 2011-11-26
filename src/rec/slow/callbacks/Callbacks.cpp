#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/slow/callbacks/SelectionCallbacks.h"

namespace rec {
namespace slow {

using command::CommandRecordTable;

void addSlowCallbacks(Instance* i, CommandRecordTable* table, int repeat) {
  addGlobalCallbacks(table);
  addInstanceCallbacks(table, i);
  addSelectionCallbacks(table, i);
  addRepeatedCallbacks(table, i, repeat);
}

}  // namespace slow
}  // namespace rec
