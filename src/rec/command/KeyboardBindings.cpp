#include <set>

#include "rec/command/KeyboardBindings.h"
#include "rec/command/Command.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace command {

using juce::XmlElement;
using slow::Position;

namespace {

const VirtualFile getBindingFile() {
  static VirtualFile vf = file::toVirtualFile("KeyPresses");
  return vf;
}

XmlElement* readKeyboardCommands(const Commands& commands) {
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

void writeKeyboardBindingFile(XmlElement* element) {
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

  data::set(fromCommandTable(t), getBindingFile());
  stl::deleteMapPointers(&t);
}

XmlElement* readKeyboardBindingFile() {
  data::TypedEditable<Commands>* e = data::editable<Commands>(getBindingFile());
  return readKeyboardCommands(e->fileReadSuccess() ? e->get() : getCommands());
}

}  // namespace

void saveKeyboardBindings(ApplicationCommandManager* commandManager) {
  ptr<juce::XmlElement> state(commandManager->getKeyMappings()->createXml(false));
  if (!state)
    LOG(ERROR) << "Couldn't create keyboard binding XML";
  else
    writeKeyboardBindingFile(state.get());
}

void loadKeyboardBindings(ApplicationCommandManager* commandManager) {
  ptr<juce::XmlElement> state(readKeyboardBindingFile());
  commandManager->getKeyMappings()->restoreFromXml(*state);
}

}  // namespace command
}  // namespace rec
