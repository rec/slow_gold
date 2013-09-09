#include <stdexcept>

#include "rec/program/JuceModel.h"

#include "rec/command/Command.pb.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/Value.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/program/JuceModelImpl.h"
#include "rec/program/Menu.pb.h"
#include "rec/program/Program.h"

using namespace rec::command;
using namespace rec::data;

namespace rec {
namespace program {

namespace {

template <typename PARTS>
bool hasProperty(const Program& program, const PARTS& parts) {
  for (auto& part: parts) {
    if (program.hasProperty(part))
      return true;
  }
  return false;
}

} // namespace

JuceModel::JuceModel(Program* p) : program_(p) {}

void JuceModel::init() {
  impl_.reset(new JuceModelImpl(program_, this));
}

JuceModel::~JuceModel() {}

void JuceModel::getAllCommands(juce::Array<CommandID>& commands) {
  for (auto& mapEntry: impl_->commandMap())
    commands.add(mapEntry.first);
}

void JuceModel::getCommandInfo(CommandID id,
                               ApplicationCommandInfo& info) {
  try {
    const command::Command& command = impl_->commandMap().at(id);
    const Description& desc = command.desc();

    int flags = command.flags();
    if (hasProperty(*program_, command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*program_, command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    const string* shortName = nullptr;
    if (command.has_setter()) {
      const Setter& setter = command.setter();
      VirtualFile file = setter.is_global() ? global() :
        program_->getCurrentFile();
      Data* data = getData(setter.type_name(), file);
      unique_ptr<Message> msg(data->clone());
      Value value = data::getMessageFieldOrDie(setter.address(), *msg);
      if (setter.type() == Setter::TOGGLE) {
        LOG_IF(DFATAL, not value.has_bool_f()) << "No boolean value.";
        if (value.bool_f())
          flags |= ApplicationCommandInfo::isTicked;
      } else {
        LOG_IF(DFATAL, not value.has_enum_f()) << "No int32 value";
        int32 index = value.enum_f();
        uint32 size = desc.menu_size();
        if (index >= size) {
          LOG(DFATAL) << "Index too large: " << index << " >= " << size;
          index = size - 1;
        }
        shortName = &desc.menu(index);
      }
    }
    if (not shortName)
      shortName = &desc.menu(0);

    info.setInfo(*shortName, desc.full(0), command.category(), flags);
    if (command.callout())
      program_->commandCallout(command, &info);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "getCommandInfo out of range " << info.commandID;
  }
}

bool JuceModel::perform(const InvocationInfo& info) {
  return impl_->perform(info);
}

StringArray JuceModel::getMenuBarNames() {
  StringArray names;
  try {
    for (auto& menu: impl_->menuBar().menu())
      names.add(menu);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menu bar";
  }
  return names;
}

ApplicationCommandManager* JuceModel::applicationCommandManager() {
  return impl_->applicationCommandManager();
}

PopupMenu JuceModel::getMenuForIndex(int menuIndex, const String&) {
  PopupMenu menu;
  try {
    const MenuBar& mb = impl_->menuBar();
    if (menuIndex >= mb.menu_size())
      LOG(DFATAL) << "out of range: " << menuIndex << " > " << mb.menu_size();
    else
      impl_->addMenu(&menu, mb.menu(menuIndex));
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menubar " << menuIndex;
  }

  return menu;
}

void JuceModel::operator()(command::ID id) {
  (*this)(id.get());
}

void JuceModel::operator()(CommandID id) {
  if (not applicationCommandManager()->invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << program_->commandName(id);
}

void JuceModel::operator()(Enable enable) {
  program_->setEnabled(enable);
}

}  // namespace program
}  // namespace rec
