#include "rec/command/TargetManager.h"

#include "rec/app/AppDirectory.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/command/Command.h"
#include "rec/command/Keyboard.xml.h"

namespace rec {
namespace command {

struct CommandCallback {
  CommandCallback(const ApplicationCommandInfo& info, Callback* cb)
      : info_(info), callback_(cb) {
  }

  ApplicationCommandInfo info_;
  ptr<Callback> callback_;
};

TargetManager::TargetManager(Component* c) : lastInvocation_(0) {
  if (c)
    c->addKeyListener(commandManager_.getKeyMappings());
  commandManager_.setFirstCommandTarget(this);
}

TargetManager:: ~TargetManager() {
  stl::deleteMapPointers(&map_);
}

void TargetManager::registerAllCommandsForTarget() {
  commandManager_.registerAllCommandsForTarget(this);
  commandManager_.registerAllCommandsForTarget(
      juce::JUCEApplication::getInstance());
  loadKeyboardBindings();
}

void TargetManager::addCommandItem(PopupMenu* menu, CommandID command,
                                   bool isActive,
                                   const String& name) {
  if (ApplicationCommandInfo* info = getInfo(command)) {
    if (name.length())
      info->shortName = name;
    info->setActive(isActive);
    addCommandItem(menu, command);
  }
}

void TargetManager::getAllCommands(juce::Array<CommandID>& commands) {
  commands.clear();
  for (CommandMap::const_iterator i = map_.begin(); i != map_.end(); ++i)
    commands.add(i->first);
}

void TargetManager::getCommandInfo(CommandID cmd, ApplicationCommandInfo& info) {
  CommandMap::const_iterator i = map_.find(cmd);
  if (i == map_.end())
    LOG(ERROR) << "Couldn't find command info";
  else
    info = i->second->info_;
}

bool TargetManager::perform(const InvocationInfo& invocation) {
  ScopedLock l(lock_);
  CommandMap::const_iterator i = map_.find(invocation.commandID);
  if (i == map_.end())
    return false;

  lastInvocation_ = invocation;
  (*(i->second->callback_))();
  return true;
}

InvocationInfo TargetManager::lastInvocation() const {
  ScopedLock l(lock_);
  return lastInvocation_;
}

void TargetManager::addCallback(Callback* cb,
                                const ApplicationCommandInfo& info) {
  CommandID id = info.commandID;
  CommandMap::const_iterator i = map_.find(id);
  if (i != map_.end()) {
    LOG(ERROR) << "Added command twice: " << id;
    delete i->second;
  }

	// DLOG(INFO) << "adding command " << id;
  map_[id] = new CommandCallback(info, cb);
}

void TargetManager::addCallback(CommandID id, Callback* cb,
                                const String& name,
                                const String& category, const String& desc) {
	addCallback(cb, makeInfo(id, name, category, desc));
}

ApplicationCommandInfo* TargetManager::getInfo(CommandID command) {
  CommandMap::iterator i = map_.find(command);
  return i == map_.end() ? NULL : &i->second->info_;
}

static File getKeyboardFile() {
  return app::getDirectory().getChildFile("Keyboard.xml");
}

void TargetManager::saveKeyboardBindings() {
  ptr<juce::XmlElement> state(commandManager_.getKeyMappings()->createXml(false));
  if (state) {
    if (!state->writeToFile(getKeyboardFile(), ""))
      LOG(ERROR) << "Couldn't write device statea file";
  }
}

void TargetManager::loadKeyboardBindings() {
  ptr<juce::XmlElement> state;
  File f = getKeyboardFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));
  else
    state.reset(Keyboard::create());

  if (state)
    commandManager_.getKeyMappings()->restoreFromXml(*state);
}

}  // namespace command
}  // namespace rec
