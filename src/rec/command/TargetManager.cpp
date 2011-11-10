#include "rec/command/TargetManager.h"

#include "rec/app/Files.h"
#include "rec/data/Data.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/command/Command.h"
#include "rec/command/map/Keyboard.xml.h"
#include "rec/slow/Position.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace command {

using slow::Position;

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
    LOG(ERROR) << "Unable to add menu item for "
               << slow::Position::commandIDName(command);
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

static const VirtualFile getKeyboardFile() {
  static VirtualFile vf = file::toVirtualFile("KeyPresses");
  return vf;
}

static void writeKeyboardFile(juce::XmlElement* element) {
  CommandTable t;
  forEachXmlChildElement(*element, mapping) {
    CommandID id = mapping->getStringAttribute("commandId").getHexValue32();
    CommandTable::const_iterator i = t.find(id);
    string key = str(mapping->getStringAttribute("key").toLowerCase());
    Command* command;
    if (i == t.end()) {
      command = new Command;
      Position::fillCommandFromId(id, command);
      t[id] = command;
    } else {
      command = i->second;
    }
    command->add_keypress(key);
  }

  data::set(fromCommandTable(t), getKeyboardFile());
  stl::deleteMapPointers(&t);
}

using juce::XmlElement;


static XmlElement* readKeyboardCommands(const Commands& commands) {
  ptr<XmlElement> element(new XmlElement("KEYMAPPINGS"));
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& cmd = commands.command(i);
    // TODO:  is this correct for multiple key assignments?
    for (int j = 0; j < cmd.keypress_size(); ++j) {
      juce::XmlElement* mapping = element->createNewChildElement("MAPPING");
      mapping->setAttribute("commandId",
                            String::toHexString(Position::toCommandID(cmd)));
      mapping->setAttribute("description", str(cmd.desc().full()));
      mapping->setAttribute("key", str(cmd.keypress(j)).toLowerCase());
    }
  }
  return element.transfer();
}

static XmlElement* readKeyboardFile() {
  data::TypedEditable<Commands>* e = data::editable<Commands>(getKeyboardFile());
  return readKeyboardCommands(e->fileReadSuccess() ? e->get() : getCommands());
}

void TargetManager::saveKeyboardBindings() {
  ptr<juce::XmlElement> state(commandManager_.getKeyMappings()->createXml(false));
  if (!state)
    LOG(ERROR) << "Couldn't create keyboard binding XML";
  else
    writeKeyboardFile(state.get());
}

void TargetManager::loadKeyboardBindings() {
  ptr<juce::XmlElement> state(readKeyboardFile());
  commandManager_.getKeyMappings()->restoreFromXml(*state);
}

}  // namespace command
}  // namespace rec
