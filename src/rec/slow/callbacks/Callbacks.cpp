#include "rec/slow/callbacks/Callbacks.h"

#include "rec/command/CallbackTable.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/RepeatedCallbacks.h"

namespace rec {
namespace slow {

using command::CallbackTable;

void addSlowCallbacks(CallbackTable* table, int repeat) {
  addGlobalCallbacks(table);
  addInstanceCallbacks(table);
  addSelectionCallbacks(table);
  addRepeatedCallbacks(table, repeat);
}

}  // namespace slow
}  // namespace rec
