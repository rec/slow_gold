#include "rec/slow/callbacks/GlobalCallbacks.h"

#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"
#include "rec/util/cd/Eject.h"

namespace rec {
namespace slow {

using command::Command;

void addGlobalCallbacks(CommandRecordTable* t) {
  addCallback(t, Command::DEL, cutNoClipboard);
  addCallback(t, Command::CUT, cutToClipboard);
  addCallback(t, Command::COPY, copyToClipboard);
  addCallback(t, Command::PASTE, pasteFromClipboard);
  addCallback(t, Command::REDO, redo);
  addCallback(t, Command::UNDO, undo);
  addCallback(t, Command::EJECT_CDS, &cd::ejectAll);
}

}  // namespace slow
}  // namespace rec
