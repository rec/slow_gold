#include "rec/util/Undo.h"
#include "rec/data/DataUpdater.h"

namespace rec {
namespace util {

using data::UndoQueue;
using data::DataUpdater;

static UndoQueue* undoQueue() { return DataUpdater::instance()->undoQueue(); }

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

void startUndo() {
  undoQueue()->start();
}

void stopUndo() {
  undoQueue()->stop();
}

void addUndoListener(Listener<None>* lst) {
  undoQueue()->addListener(lst);
}

}  // namespace util
}  // namespace rec
