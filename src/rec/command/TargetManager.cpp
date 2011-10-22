#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/command/Command.h"
#include "rec/command/map/Keyboard.xml.h"
#include "rec/slow/Position.h"

namespace rec {
namespace command {

namespace {

ApplicationCommandInfo makeInfo(
    CommandID id, const String& name,
    const String& category, const String& desc,
    int flags = 0, int keyCode = 0,
    const ModifierKeys& mod = ModifierKeys());

juce::ApplicationCommandInfo makeInfo(CommandID id, const String& name,
                                      const String& category, const String& desc,
                                      int flags, int key, const ModifierKeys& mod) {
  ApplicationCommandInfo i(id);
  i.setInfo(name, desc, category, flags);
  if (key)
    i.addDefaultKeypress(key, mod);

  if (category == "(None)")
    i.flags |= ApplicationCommandInfo::hiddenFromKeyEditor;

  return i;
}

}  // namespace

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
    DCHECK(info->shortName.length()) << "No name for command "
                                     << slow::Position::commandIDName(command);
    info->setActive(isActive);
    menu->addCommandItem(&commandManager_, command);
  } else {
    DLOG(ERROR) << "Unable to add menu item " << str(info->shortName)
                << " for " << command;
  }
}

void TargetManager::getAllCommands(juce::Array<CommandID>& commands) {
  commands.clear();
  for (CommandCallbackMap::iterator i = map_.begin(); i != map_.end(); ++i) {
    commands.add(i->first);
  }
}

void TargetManager::getCommandInfo(CommandID cmd, ApplicationCommandInfo& info) {
  CommandCallbackMap::const_iterator i = map_.find(cmd);
  if (i == map_.end())
    LOG(ERROR) << "No getCommandInfo" << slow::Position::commandIDName(cmd);
  else
    info = i->second->info_;
  DCHECK(info.shortName.isNotEmpty()) << slow::Position::commandIDName(cmd);
}

bool TargetManager::perform(const InvocationInfo& invocation) {
  ScopedLock l(lock_);
  CommandCallbackMap::const_iterator i = map_.find(invocation.commandID);
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

void TargetManager::addCallback(CommandID id, Callback* cb,
                                const String& name,
                                const String& category,
                                const String& desc) {
  if (!(category.isNotEmpty() && name.isNotEmpty() && desc.isNotEmpty())) {
    LOG(ERROR) << "Can't add " << slow::Position::commandIDName(id)
               << ", " << name << ", " << desc;
    return;
  }

  ApplicationCommandInfo info = makeInfo(id, name, category, desc);
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

static File getKeyboardFile() {
  return app::getAppFile("Keyboard.xml");
}

void TargetManager::saveKeyboardBindings() {
  ptr<juce::XmlElement> state(commandManager_.getKeyMappings()->createXml(false));
  if (state) {
    if (!state->writeToFile(getKeyboardFile(), ""))
      LOG(ERROR) << "Couldn't write device state file.";
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
