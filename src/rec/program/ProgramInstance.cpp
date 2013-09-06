#include <stdexcept>

#include "rec/program/ProgramInstance.h"

#include "rec/program/ProgramInstanceImpl.h"
#include "rec/program/Program.h"
#include "rec/command/Command.pb.h"
#include "rec/program/Menu.pb.h"

using namespace rec::command;

namespace rec {
namespace app {

ProgramInstance::ProgramInstance(Program* p) : impl_(new Impl(p)) {}
ProgramInstance::~ProgramInstance() {}

void ProgramInstance::getAllCommands(juce::Array<CommandID>& commands) {
  for (auto& mapEntry: impl_->programMap())
    commands.add(mapEntry.first);
}

void ProgramInstance::getCommandInfo(CommandID command,
                                     ApplicationCommandInfo& info) {
  try {
    const Command& command = impl_->programMap().at(info.commandID);
    const Description& desc = command.desc();
    int flags = command.flags();
    if (hasProperty(*impl_->program(), command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*impl_->program(), command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    info.setInfo(desc.name(), desc.menu(0), command.category(), flags);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "getCommandInfo out of range " << info.commandID;
  }
}

bool ProgramInstance::perform(const InvocationInfo& info) {
  return impl_->perform(info);
}

StringArray ProgramInstance::getMenuBarNames() {
  StringArray names;
  try {
    for (auto& menu: impl_->menuBar().menu())
      names.add(menu);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menu bar";
  }
  return names;
}

ApplicationCommandManager* ProgramInstance::applicationCommandManager() {
  return impl_->applicationCommandManager();
}

PopupMenu ProgramInstance::getMenuForIndex(int menuIndex,
                                           const String&) {
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

}  // namespace app
}  // namespace rec
