#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include <map>

#include "rec/data/Editable.h"

namespace rec {
namespace data {

void needsUpdate(UntypedEditable*);
void addToUndoQueue(UntypedEditable* u, const OperationList& q);

EditableMap* editableMap();
CriticalSection* editableMapLock();

void start();
void stop();

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
