#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/slow/callbacks/SelectionCallbacks.h"

namespace rec {
namespace slow {

using command::CallbackTable;

CallbackTable* createCallbackTable(Instance* i) {
  ptr<CallbackTable> t;
  addGlobalCallbacks(t.get());
  addInstanceCallbacks(t.get(), i);
  addSelectionCallbacks(t.get(), i);
  addRepeatedCallbacks(t.get(), i, REPEATED_COUNT);

  return t.transfer();
}

}  // namespace slow
}  // namespace rec
