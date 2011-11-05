#ifndef __REC_DATA_EDITABLE_FACTORY__
#define __REC_DATA_EDITABLE_FACTORY__

#include <map>

#include "rec/data/Editable.h"

namespace rec {

namespace util { class DefaultRegistry; }

namespace data {

void needsUpdate(UntypedEditable*);
void addToUndoQueue(UntypedEditable* u, const OperationList& undo,
                    const OperationList& command);

EditableMap* editableMap();
CriticalSection* editableMapLock();

void start(DefaultRegistry* registry);
void stop();

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_EDITABLE_FACTORY__
