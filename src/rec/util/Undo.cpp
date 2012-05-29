#include "rec/util/Undo.h"
#include "rec/data/DataCenter.h"
#include "rec/data/UndoStack.h"

namespace rec {
namespace util {

using data::UndoStack;

static UndoStack* undoStack() { return data::getDataCenter().undo_.get(); }

// How many commands have been undone?
int undoes() {
  return undoStack()->undoes();
}

// How many commands can be undone?
int undoable() {
  return undoStack()->undoable();
}

void undo() {
  undoStack()->undo();
}

void redo() {
  undoStack()->redo();
}

void addUndoListener(Listener<None>* lst) {
  undoStack()->addListener(lst);
}

}  // namespace util
}  // namespace rec
