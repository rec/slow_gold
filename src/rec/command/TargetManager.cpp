#include "rec/command/TargetManager.h"

#include "rec/data/persist/AppDirectory.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/command/Command.h"

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
  return getApplicationDirectory().getChildFile("Keyboard.xml");
}

void TargetManager::saveKeyboardBindings() {
  ptr<juce::XmlElement> state(commandManager_.getKeyMappings()->createXml(false));
  if (state) {
    if (!state->writeToFile(getKeyboardFile(), ""))
      LOG(ERROR) << "Couldn't write device statea file";
  }
}


static const char KEYBOARD_MAPPINGS[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
""
"<KEYMAPPINGS basedOnDefaults=\"0\">"
"  <MAPPING commandId=\"1001\" description=\"Quits the application\" key=\"command + Q\"/>"
"  <MAPPING commandId=\"1\" description=\"Add a loop point at the current time.\""
"           key=\"command + =\"/>"
"  <MAPPING commandId=\"1\" description=\"Add a loop point at the current time.\""
"           key=\".\"/>"
"  <MAPPING commandId=\"1e\" description=\"Select loop 1 and unselect all other loops.\""
"           key=\"command + 1\"/>"
"  <MAPPING commandId=\"1f\" description=\"Select loop 2 and unselect all other loops.\""
"           key=\"command + 2\"/>"
"  <MAPPING commandId=\"20\" description=\"Select loop 3 and unselect all other loops.\""
"           key=\"command + 3\"/>"
"  <MAPPING commandId=\"21\" description=\"Select loop 4 and unselect all other loops.\""
"           key=\"command + 4\"/>"
"  <MAPPING commandId=\"22\" description=\"Select loop 5 and unselect all other loops.\""
"           key=\"command + 5\"/>"
"  <MAPPING commandId=\"23\" description=\"Select loop 6 and unselect all other loops.\""
"           key=\"command + 6\"/>"
"  <MAPPING commandId=\"24\" description=\"Select loop 7 and unselect all other loops.\""
"           key=\"command + 7\"/>"
"  <MAPPING commandId=\"25\" description=\"Select loop 8 and unselect all other loops.\""
"           key=\"command + 8\"/>"
"  <MAPPING commandId=\"26\" description=\"Select loop 9 and unselect all other loops.\""
"           key=\"command + 9\"/>"
"  <MAPPING commandId=\"27\" description=\"Select loop 10 and unselect all other loops.\""
"           key=\"command + 0\"/>"
"  <MAPPING commandId=\"2\" description=\"Open the Audio Preferences pane.\""
"           key=\"command + ;\"/>"
"  <MAPPING commandId=\"8\" description=\"Immediately jump to the next loop point and select it.\""
"           key=\"cursor right\"/>"
"  <MAPPING commandId=\"9\" description=\"Immediately jump to the previous segment and select it.\""
"           key=\"cursor left\"/>"
"  <MAPPING commandId=\"32\" description=\"Start or pause\" key=\"spacebar\"/>"
"  <MAPPING commandId=\"32\" description=\"Start or pause\" key=\"command + spacebar\"/>"
"  <MAPPING commandId=\"a\" description=\"Jump to the last segment and select it.\""
"           key=\"return\"/>"
"  <MAPPING commandId=\"a\" description=\"Jump to the last segment and select it.\""
"           key=\"command + return\"/>"
"  <MAPPING commandId=\"13\" description=\"Unselect everything selected and vice-versa.\""
"           key=\"command + I\"/>"
"  <MAPPING commandId=\"28\" description=\"Toggle loop 1 between selected and unselected\""
"           key=\"1\"/>"
"  <MAPPING commandId=\"29\" description=\"Toggle loop 2 between selected and unselected\""
"           key=\"2\"/>"
"  <MAPPING commandId=\"2a\" description=\"Toggle loop 3 between selected and unselected\""
"           key=\"3\"/>"
"  <MAPPING commandId=\"2b\" description=\"Toggle loop 4 between selected and unselected\""
"           key=\"4\"/>"
"  <MAPPING commandId=\"2c\" description=\"Toggle loop 5 between selected and unselected\""
"           key=\"5\"/>"
"  <MAPPING commandId=\"2d\" description=\"Toggle loop 6 between selected and unselected\""
"           key=\"6\"/>"
"  <MAPPING commandId=\"2e\" description=\"Toggle loop 7 between selected and unselected\""
"           key=\"7\"/>"
"  <MAPPING commandId=\"2f\" description=\"Toggle loop 8 between selected and unselected\""
"           key=\"8\"/>"
"  <MAPPING commandId=\"30\" description=\"Toggle loop 9 between selected and unselected\""
"           key=\"9\"/>"
"  <MAPPING commandId=\"31\" description=\"Toggle loop 10 between selected and unselected\""
"           key=\"0\"/>"
"  <MAPPING commandId=\"3c\" description=\"Unselect loop 1 only\" key=\"option + 1\"/>"
"  <MAPPING commandId=\"3d\" description=\"Unselect loop 2 only\" key=\"option + 2\"/>"
"  <MAPPING commandId=\"3e\" description=\"Unselect loop 3 only\" key=\"option + 3\"/>"
"  <MAPPING commandId=\"3f\" description=\"Unselect loop 4 only\" key=\"option + 4\"/>"
"  <MAPPING commandId=\"40\" description=\"Unselect loop 5 only\" key=\"option + 5\"/>"
"  <MAPPING commandId=\"41\" description=\"Unselect loop 6 only\" key=\"option + 6\"/>"
"  <MAPPING commandId=\"42\" description=\"Unselect loop 7 only\" key=\"option + 7\"/>"
"  <MAPPING commandId=\"43\" description=\"Unselect loop 8 only\" key=\"option + 8\"/>"
"  <MAPPING commandId=\"44\" description=\"Unselect loop 9 only\" key=\"option + 9\"/>"
"  <MAPPING commandId=\"45\" description=\"Unselect loop 10 only\" key=\"option + 0\"/>"
"  <MAPPING commandId=\"1002\" description=\"Delete the current selection without changing the clipboard.\""
"           key=\"backspace\"/>"
"  <MAPPING commandId=\"1003\" description=\"Copy the current selection to the clipboard and clear the selection.\""
"           key=\"command + X\"/>"
"  <MAPPING commandId=\"1003\" description=\"Copy the current selection to the clipboard and clear the selection.\""
"           key=\"shift + command + X\"/>"
"  <MAPPING commandId=\"1003\" description=\"Copy the current selection to the clipboard and clear the selection.\""
"           key=\"option + command + X\"/>"
"  <MAPPING commandId=\"1004\" description=\"Copy the current selection to the clipboard.\""
"           key=\"command + C\"/>"
"  <MAPPING commandId=\"1005\" description=\"Replace the current selection with a copy of the clipboard.\""
"           key=\"command + V\"/>"
"  <MAPPING commandId=\"6\" description=\"Close the current file\" key=\"command + W\"/>"
"  <MAPPING commandId=\"7\" description=\"Eject all CDs and DVDs\" key=\"command + E\"/>"
"  <MAPPING commandId=\"f\" description=\"Open a dialog to select a new audio file for looping.\""
"           key=\"command + O\"/>"
"  <MAPPING commandId=\"11\" description=\"Edit midi mappings for commands.\""
"           key=\"command + M\"/>"
"  <MAPPING commandId=\"12\" description=\"Edit keyboard mappings for commands.\""
"           key=\"command + K\"/>"
"  <MAPPING commandId=\"1006\" description=\"Select all of the file\" key=\"command + A\"/>"
"  <MAPPING commandId=\"1007\" description=\"Select none of the file\" key=\"command + D\"/>"
"  <MAPPING commandId=\"49\" description=\"Enable the next segment in order.\""
"           key=\"command + cursor right\"/>"
"  <MAPPING commandId=\"4a\" description=\"Enable the segment before the first one.\""
"           key=\"command + cursor left\"/>"
"  <MAPPING commandId=\"4b\" description=\"Disable the last loop segment\" key=\"option + cursor right\"/>"
"  <MAPPING commandId=\"4c\" description=\"Disable the first loop segment\" key=\"option + cursor left\"/>"
"  <MAPPING commandId=\"3b\" description=\"Nudge gain down by 2dB\" key=\"cursor up\"/>"
"  <MAPPING commandId=\"48\" description=\"Nudge gain up by 2dB\" key=\"cursor down\"/>"
"  <MAPPING commandId=\"4d\" description=\"Toggle audio dim on and off.\" key=\"numpad .\"/>"
"  <MAPPING commandId=\"4e\" description=\"Toggle audio mute on and off.\" key=\"numpad 0\"/>"
"  <MAPPING commandId=\"4f\" description=\"Reset audio level to 0 dB\" key=\"numpad 1\"/>"
"  <MAPPING commandId=\"14\" description=\"Select loop 1.\" key=\"shift + !\"/>"
"  <MAPPING commandId=\"15\" description=\"Select loop 2.\" key=\"shift + @\"/>"
"  <MAPPING commandId=\"16\" description=\"Select loop 3.\" key=\"shift + #\"/>"
"  <MAPPING commandId=\"17\" description=\"Select loop 4.\" key=\"shift + $\"/>"
"  <MAPPING commandId=\"18\" description=\"Select loop 5.\" key=\"shift + %\"/>"
"  <MAPPING commandId=\"19\" description=\"Select loop 6.\" key=\"shift + ^\"/>"
"  <MAPPING commandId=\"1a\" description=\"Select loop 7.\" key=\"shift + &\"/>"
"  <MAPPING commandId=\"1b\" description=\"Select loop 8.\" key=\"shift + *\"/>"
"  <MAPPING commandId=\"1c\" description=\"Select loop 9.\" key=\"shift + (\"/>"
"  <MAPPING commandId=\"1d\" description=\"Select loop 10.\" key=\"shift + )\"/>"
"</KEYMAPPINGS>";

void TargetManager::loadKeyboardBindings() {
  ptr<juce::XmlElement> state;
  File f = getKeyboardFile();
  if (f.exists())
    state.reset(juce::XmlDocument::parse(f));
  else
    state.reset(juce::XmlDocument::parse(KEYBOARD_MAPPINGS));

  if (state)
    commandManager_.getKeyMappings()->restoreFromXml(*state);
}

}  // namespace command
}  // namespace rec

