#include "rec/util/Undo.h"
#include "rec/data/DataUpdater.h"

namespace rec {
namespace util {

using data::UndoStack;
using data::DataUpdater;

static UndoStack* undoStack() { return DataUpdater::instance()->undoStack(); }

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

void startUndo() {
  undoStack()->start();
}

void stopUndo() {
  undoStack()->stop();
}

void addUndoListener(Listener<None>* lst) {
  undoStack()->addListener(lst);
}

}  // namespace util
}  // namespace rec
