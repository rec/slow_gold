#include "rec/program/ProgramBase.h"

#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace program {

void ProgramBase::addCallback(CommandID command, unique_ptr<Callback> callback) {
  auto loc = callbackMap_.find(command);
  if (loc == callbackMap_.end())
    callbackMap_.insert(loc, std::make_pair(command, std::move(callback)));
  else
    LOG(DFATAL) << "Duplicate command ID " << commandName(command);
}

Callback* ProgramBase::getCallback(CommandID command) const {
  Callback* callback = nullptr;
  auto loc = callbackMap_.find(command);
  if (loc != callbackMap_.end())
    callback = loc->second.get();
  LOG_IF(DFATAL, not callback) << "No callback for " << commandName(command);
  return callback;
}

bool ProgramBase::hasProperty(const string& name) const {
  if (name == "cant_copy")
    return not canCopy();

  if (name == "cant_cut")
    return not canCut();

  if (name == "cant_paste")
    return not canPaste();

  if (name == "cant_redo")
    return not canUndo();

  if (name == "cant_undo")
    return not canRedo();

  return false;
}

}  // namespace program
}  // namespace rec

