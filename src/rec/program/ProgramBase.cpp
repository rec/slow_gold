#include "rec/program/ProgramBase.h"

#include "rec/gui/menu/RecentFiles.h"
#include "rec/program/Threads.pb.h"
#include "rec/util/BinaryMacros.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace program {

void ProgramBase::addCallback(CommandID command, unique_ptr<Callback> callback) {
  auto loc = callbackMap_.find(command);
  if (loc == callbackMap_.end())
    callbackMap_.insert(loc, std::make_pair(command, std::move(callback)));
  else
    LOG(DFATAL) << "Duplicate command CommandID " << idToName(command);
}

Callback* ProgramBase::getCallback(CommandID command) const {
  Callback* callback = nullptr;
  auto loc = callbackMap_.find(command);
  if (loc != callbackMap_.end())
    callback = loc->second.get();
  LOG_IF(ERROR, not callback) << "No callback for " << idToName(command);
  return callback;
}

ProgramBase::ProgramBase() : enabled_(true) {
  registerProgram(this);
}

ProgramBase::~ProgramBase() {
  registerProgram(nullptr);
}

bool ProgramBase::isEnabled() const {
  Lock l(lock_);
  return enabled_;
}

void ProgramBase::setEnabled(bool enabled) {
  Lock l(lock_);
  enabled_ = enabled;
}

}  // namespace program
}  // namespace rec

