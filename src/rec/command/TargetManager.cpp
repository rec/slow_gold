#include "rec/command/TargetManagerManager.h"

#include "rec/util/thread/Callback.h"
#include "rec/command/Command.h"

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

TargetManager::TargetManager(Component* c) {
  commandManager_.registerAllCommandsForTargetManager(&target_);
  commandManager_.registerAllCommandsForTargetManager(JUCEApplication::getInstance());
  if (c)
    addComponent(c);
}

void TargetManager::addComponent(Component* c)
  c->addKeyListener(commandManager_.getKeyMappings());
  c->setApplicationCommandManagerToWatch(&commandManager_);
}

void TargetManager::getAllCommands(Array<CommandID>& commands) {
  commands.clear();
  for (CommandMap::const_iterator i = map_.begin(); i != map_.end(); ++i)
    commands.add(i->first);
}

void TargetManager::getCommandInfo(CommandID cmd, ApplicationCommandInfo& info) {
  CommandMap::const_iterator i = map_.find(cmd);
  if (i == map_.end())
    LOG(ERROR) << "Couldn't find command info";
  else
    info = *(i->second->info_);
}

bool TargetManager::perform(const InvocationInfo& invocation) {
  ScopedLock l(lock_);
  CommandMap::const_iterator i = map_.find(invocation.commandID);
  if (i == map_.end())
    return false;

  lastInvocation_ = invocation;
  *(i->second->callback_)();
  return false;
}

InvocationInfo TargetManager::lastInvocation() const {
  ScopedLock l(lock_);
  return lastInvocation_;
}

void TargetManager::add(thread::Callback* cb, const ApplicationCommandInfo& info) {
  CommandID id = info.commandID;
  CommandMap::const_iterator i = map_.find(id);
  if (i != map_.end()) {
    LOG(ERROR) << "Added command twice: " << id;
    delete i->second;
  }

  map_[id] = new CommandCallback(info, cb);
}

void TargetManager::add(CommandID id, thread::Callback* cb,
                        const String& name,
                        const String& category, const String& desc,
                        int keyCode,
                        const ModifierKeys& modifiers,
                        int flags) {
  return add(cb, makeInfo(id, name, category, desc, flags, keyCode, modifiers));
}

}  // namespace command
}  // namespace rec

