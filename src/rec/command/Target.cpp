#include "rec/command/Target.h"

#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

namespace {

struct CommandCallback {
  CommandCallback(const ApplicationCommandInfo& info, thread::Callback* cb)
      : info_(info), callback_(cb) {
  }

  ApplicationCommandInfo info_;
  ptr<thread::Callback> callback_;
};

}

void Target::getAllCommands(Array<CommandID>& commands) {
  commands.clear();
  for (CommandMap::const_iterator i = map_.begin(); i != map_.end(); ++i)
    commands.add(i->first);
}

void Target::getCommandInfo(CommandID cmd, ApplicationCommandInfo& info) {
  CommandMap::const_iterator i = map_.find(cmd);
  if (i == map_.end())
    LOG(ERROR) << "Couldn't find command info";
  else
    info = *(i->second->info_);
}

bool Target::perform(const InvocationInfo& invocation) {
  ScopedLock l(lock_);
  CommandMap::const_iterator i = map_.find(invocation.commandID);
  if (i == map_.end())
    return false;

  lastInvocation_ = invocation;
  *(i->second->callback_)();
  return false;
}

InvocationInfo Target::lastInvocation() const {
  ScopedLock l(lock_);
  return lastInvocation_;
}

void Target::add(thread::Callback* cb, const ApplicationCommandInfo& info) {
  CommandID id = info.commandID;
  CommandMap::const_iterator i = map_.find(id);
  if (i != map_.end()) {
    LOG(ERROR) << "Added command twice: " << id;
    delete i->second;
  }

  map_[id] = new CommandCallback(info, cb);
}

void Target::add(thread::Callback* callback, CommandID id, const String& name,
                 const String& desc, const String& category, int flags) {
  ApplicationCommandInfo info(id);
  info.setInfo(name, desc, category, flags);
  add(cb, info);
}

}  // namespace commandtarget
}  // namespace rec
