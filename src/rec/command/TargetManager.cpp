#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/command/Command.h"
#include "rec/command/map/Keyboard.xml.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

using slow::Position;

struct CommandCallback {
  CommandCallback(const ApplicationCommandInfo& info, Callback* cb)
      : info_(info), callback_(cb) {
  }

  ApplicationCommandInfo info_;
  ptr<Callback> callback_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandCallback);
};

TargetManager::TargetManager(Component* c, Listener<None>* listener)
    : context_(new CommandContext(listener)),
      lastInvocation_(0),
      disabled_(false) {
  c->addKeyListener(commandManager_.getKeyMappings());
  commandManager_.setFirstCommandTarget(this);
}

TargetManager:: ~TargetManager() {}

void TargetManager::registerAllCommandsForTarget() {
  commandManager_.registerAllCommandsForTarget(this);
  loadKeyboardBindings(this);
}

void TargetManager::getAllCommands(juce::Array<CommandID>& commands) {
  commands.clear();
  for (CommandCallbackMap::iterator i = map_.begin(); i != map_.end(); ++i)
    commands.add(i->first);
}

void TargetManager::getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
  Lock l(lock_);
  CommandCallbackMap::const_iterator i = map_.find(id);
  if (i == map_.end())
    LOG(ERROR) << "No getCommandInfo" << slow::Position::commandIDName(id);
  else
    info = i->second->info_;

  if (!info.shortName.isNotEmpty())
    LOG(ERROR) << "No name for " << slow::Position::commandIDName(id);
}

bool TargetManager::perform(const InvocationInfo& invocation) {
  Lock l(lock_);
  if (disabled_)
    return true;

  CommandID id = invocation.commandID;
  CommandCallbackMap::const_iterator i = map_.find(id);
  if (i == map_.end())
    return false;

  lastInvocation_ = invocation;
  (*(i->second->callback_))();
  return true;
}

InvocationInfo TargetManager::lastInvocation() const {
  Lock l(lock_);
  return lastInvocation_;
}

void TargetManager::addCallback(CommandID id, Callback* cb,
                                const String& name,
                                const String& category,
                                const String& desc) {
  if (!(category.isNotEmpty() && name.isNotEmpty() && desc.isNotEmpty())) {
    LOG(ERROR) << "Can't add " << slow::Position::commandIDName(id)
               << ", " << name << ", " << desc;
    return;
  }

  ApplicationCommandInfo info(id);
  int flags = 0;
  if (category == "" || category == "(None)")
    flags = ApplicationCommandInfo::hiddenFromKeyEditor;
  info.setInfo(name, desc, category, flags);

  CommandCallbackMap::const_iterator i = map_.find(id);
  if (i != map_.end()) {
    LOG(ERROR) << "Added command twice: " << id;
    delete i->second;
  }

  map_[id] = new CommandCallback(info, cb);
}

ApplicationCommandInfo* TargetManager::getInfo(CommandID command) {
  CommandCallbackMap::iterator i = map_.find(command);
  return i == map_.end() ? NULL : &i->second->info_;
}

void TargetManager::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                                   const String& name) {
  if (ApplicationCommandInfo* info = getInfo(id)) {
    if (name.length()) {
      info->shortName = name;
    } else {
      SetterTable::const_iterator i = context_->setters_.find(id);
      if (i != context_->setters_.end())
        info->shortName = str(i->second->menuName());
    }
    if (!info->shortName.length())
      LOG(ERROR) << "No name for command " << slow::Position::commandIDName(id);
    info->setActive(enable);
    menu->addCommandItem(commandManager(), id, name);
  } else {
    LOG(ERROR) << "Can't add item " << Position::commandIDName(id);
  }
}

}  // namespace command
}  // namespace rec
