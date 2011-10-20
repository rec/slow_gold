#include "rec/slow/GlobalCommands.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

void addGlobalCommands(CallbackTable* t) {
  (*t)[Command::DEL] = functionCallback(cutNoClipboard);
  (*t)[Command::CUT] = functionCallback(cutToClipboard);
  (*t)[Command::COPY] = functionCallback(copyToClipboard);
  (*t)[Command::PASTE] = functionCallback(pasteFromClipboard);
  (*t)[Command::REDO] = functionCallback(redo);
  (*t)[Command::UNDO] = functionCallback(undo);
}

}  // namespace slow
}  // namespace rec
