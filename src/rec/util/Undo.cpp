#include "rec/util/Undo.h"
#include "rec/data/persist/EditableUpdater.h"

namespace rec {
namespace util {

using data::UndoQueue;
using data::EditableUpdater;

static UndoQueue* uqueue() { return EditableUpdater::instance()->undoQueue(); }

// How many commands have been undone?
int undoes() {
  return uqueue()->undoes();
}

// How many commands can be undone?
int undoable() {
  return uqueue()->undoable();
}

void undo() {
}

void redo() {
}

}  // namespace util
}  // namespace rec
