#ifndef __REC_DATA_INTERNAL__
#define __REC_DATA_INTERNAL__

#include "rec/data/Editable.h"

namespace rec {
namespace data {

void needsUpdate(UntypedEditable*);
void addToUndoQueue(UntypedEditable* u, const OperationList& undo,
                    const OperationList& command);

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_INTERNAL__
