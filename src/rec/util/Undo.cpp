#include "rec/util/Undo.h"
#include "rec/data/persist/EditableUpdater.h"

namespace rec {
namespace util {

using data::UndoQueue;
using data::EditableUpdater;

static UndoQueue* undoQueue() { return EditableUpdater::instance()->undoQueue(); }

// How many commands have been undone?
int undoes() {
  return undoQueue()->undoes();
}

// How many commands can be undone?
int undoable() {
  return undoQueue()->undoable();
}

void undo() {
  undoQueue()->undo();
}

void redo() {
  undoQueue()->redo();
}

void enableUndo(bool enabled) {
  undoQueue()->enableUndo(enabled);
}

}  // namespace util
}  // namespace rec
