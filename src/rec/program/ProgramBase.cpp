#include "rec/program/ProgramBase.h"

#include "rec/gui/menu/RecentFiles.h"
#include "rec/program/Threads.pb.h"
#include "rec/util/Binary.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace program {

void ProgramBase::addCallback(CommandID command, unique_ptr<Callback> callback) {
  auto loc = callbackMap_.find(command);
  if (loc == callbackMap_.end())
    callbackMap_.insert(loc, std::make_pair(command, std::move(callback)));
  else
    LOG(DFATAL) << "Duplicate command CommandID " << commandName(command);
}

Callback* ProgramBase::getCallback(CommandID command) const {
  Callback* callback = nullptr;
  auto loc = callbackMap_.find(command);
  if (loc != callbackMap_.end())
    callback = loc->second.get();
  LOG_IF(ERROR, not callback) << "No callback for " << commandName(command);
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

  if (name == "recent_empty")
    return gui::recentFilesEmpty();

  return false;
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

ThreadProtos ProgramBase::threads() const {
  return BINARY_PROTO(Threads, ThreadProtos);
}

gui::Layouts ProgramBase::layouts() const {
  return BINARY_PROTO(Layout, gui::Layouts);
}

gui::ComponentProtos ProgramBase::components() const {
  return BINARY_PROTO(Components, gui::ComponentProtos);
}

}  // namespace program
}  // namespace rec

