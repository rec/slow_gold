#include "rec/slow/callbacks/Callbacks.h"

#include "rec/slow/callbacks/ApplyCallbacks.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/RepeatedCallbacks.h"

namespace rec {
namespace slow {

void addSlowCallbacks(program::Program* table, int repeat) {
  addGlobalCallbacks(table);
  addInstanceCallbacks(table);
  addApplyCallbacks(table);
  addSelectionCallbacks(table);
  addRepeatedCallbacks(table, repeat);
}

}  // namespace slow
}  // namespace rec
