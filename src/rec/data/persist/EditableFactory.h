#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include <map>

#include "rec/data/Editable.h"

namespace rec {
namespace data {

class DefaultRegistry;

void needsUpdate(UntypedEditable*);
void addToUndoQueue(UntypedEditable* u, const OperationList& undo,
                    const OperationList& command);

DefaultRegistry* defaultRegistry();
EditableMap* editableMap();
CriticalSection* editableMapLock();

void start(DefaultRegistry* registry);
void stop();

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
