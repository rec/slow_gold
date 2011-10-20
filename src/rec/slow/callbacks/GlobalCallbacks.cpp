#include "rec/slow/callbacks/GlobalCallbacks.h"

#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"
#include "rec/util/cd/Eject.h"

namespace rec {
namespace slow {

void addGlobalCallbacks(CallbackTable* t) {
  add(t, Command::DEL, cutNoClipboard);
  add(t, Command::CUT, cutToClipboard);
  add(t, Command::COPY, copyToClipboard);
  add(t, Command::PASTE, pasteFromClipboard);
  add(t, Command::REDO, redo);
  add(t, Command::UNDO, undo);
  add(t, Command::EJECT_CDS, &cd::ejectAll);
}

}  // namespace slow
}  // namespace rec
