#ifndef __REC_UTIL_UNDO__
#define __REC_UTIL_UNDO__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace util {

// How many commands have been undone?
int undoes();

// How many commands can be undone?
int undoable();

inline bool canRedo() { return undoes(); }
inline bool canUndo() { return undoable(); }

void undo();
void redo();

void startUndo();
void stopUndo();

void addUndoListener(Listener<None>*);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UNDO__
