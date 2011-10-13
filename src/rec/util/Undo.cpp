#include "rec/util/Undo.h"

namespace rec {
namespace util {

// How many commands have been undone?
int undoes() {
  return 0;
}

// How many commands can be undone?
int undoable() {
  return 0;
}

void undo() {
}

void redo() {
}

}  // namespace util
}  // namespace rec
