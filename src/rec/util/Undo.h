#ifndef __REC_UTIL_UNDO__
#define __REC_UTIL_UNDO__

#include "rec/util/Listener.h"

namespace rec {
namespace util {

// How many commands have been undone?
int undoes();

// How many commands can be undone?
int undoable();

inline bool canRedo() { return undoes() != 0; }

inline bool canUndo() { return undoable() != 0; }

void undo();
void redo();

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UNDO__
