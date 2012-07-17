#include <map>
#include <set>

#include "rec/command/KeyboardBindings.h"
#include "rec/command/Command.h"
#include "rec/command/TargetManager.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace command {

using juce::XmlElement;

namespace {

VirtualFile makeKeyboardVirtualFile() {
  VirtualFile f;
  f.set_type(VirtualFile::VOLUME);
  f.add_path("KeyPresses");
  return f;
};

const VirtualFile& getKeyboardBindingFile() {
  static VirtualFile vf = makeKeyboardVirtualFile();
  return vf;
}

XmlElement* readKeyboardCommands(const Commands& cmds, const Commands& lib) {
  typedef std::map<int, const Command*> CommandMap;
  CommandMap cmap;
  for (int i = 0; i < lib.command_size(); ++i)
    cmap[lib.command(i).type()] = &lib.command(i);

  ptr<XmlElement> element(new XmlElement("KEYMAPPINGS"));
  for (int i = 0; i < cmds.command_size(); ++i) {
    const Command& cmd = cmds.command(i);
    CommandMap::const_iterator j = cmap.find(cmd.type());
    if (j == cmap.end()) {
      LOG(DFATAL) << "Didn't find command " << cmd.ShortDebugString();
      continue;
    } else if (!j->second->desc().full_size()) {
      LOG(DFATAL) << "Empty description " << cmd.ShortDebugString();
      continue;
    }

    string desc = j->second->desc().full(0);
    // TODO:  is this correct for multiple key assignments?
    for (int k = 0; k < cmd.keypress_size(); ++k) {
      juce::XmlElement* mapping = element->createNewChildElement("MAPPING");
      mapping->setAttribute("commandId",
                            String::toHexString(CommandIDEncoder::toCommandID(cmd)));
      mapping->setAttribute("description", str(desc));
      mapping->setAttribute("key", str(cmd.keypress(k)).toLowerCase());
    }
  }
  return element.transfer();
}

void writeKeyboardBindingFile(XmlElement* element) {
  CommandRecordTable table;
  forEachXmlChildElement(*element, mapping) {
    CommandID id = mapping->getStringAttribute("commandId").getHexValue32();
    CommandRecord* cr = table.find(id);
    string key = str(mapping->getStringAttribute("key").toLowerCase());
    if (!cr->command_) {
      cr->command_.reset(new Command);
      CommandIDEncoder::fillCommandFromId(id, cr->command_.get());
    }
    cr->command_->add_keypress(key);
  }

  data::setProto(table.getCommands(), getKeyboardBindingFile());
}

XmlElement* readKeyboardBindingFile(const Commands& commands) {
  const VirtualFile& f = getKeyboardBindingFile();
  data::Data* d = data::getData<Commands>(f);
  return readKeyboardCommands(d->fileReadSuccess() ?
  	                          data::getProto<Commands>(d) : commands,
                              commands);
}

}  // namespace

void saveKeyboardBindings(ApplicationCommandManager* commandManager) {
  ptr<juce::XmlElement> state(commandManager->getKeyMappings()->createXml(false));
  if (!state)
    LOG(DFATAL) << "Couldn't create keyboard binding XML";
  else
    writeKeyboardBindingFile(state.get());
}

void loadKeyboardBindings(TargetManager* target) {
  const CommandRecordTable& table = *target->commandRecordTable();
  ptr<juce::XmlElement> state(readKeyboardBindingFile(table.getCommands()));
  target->commandManager()->getKeyMappings()->restoreFromXml(*state);
}

void clearKeyboardBindings(TargetManager* target) {
  const Commands& commands = target->commandRecordTable()->getCommands();
  ptr<juce::XmlElement>(readKeyboardCommands(commands, commands));
  saveKeyboardBindings(target->commandManager());
}

}  // namespace command
}  // namespace rec
