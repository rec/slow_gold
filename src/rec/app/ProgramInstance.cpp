#include <stdexcept>

#include "rec/app/ProgramInstance.h"
#include "rec/app/Program.h"

namespace rec {
namespace app {

using namespace rec::command;

namespace {

ProgramInstance::ProgramMap makeProgramMap(const Program& program) {
  ProgramInstance::ProgramMap programMap;
  for (auto& command: program.commands().command())
    programMap[command.command()] = command;

  for (auto& command: program.keypresses().command()) {
    try {
      *programMap.at(command.command()).mutable_keypress() = command.keypress();
    } catch (const std::out_of_range&) {
      LOG(DFATAL) << "Out of range keypress command." << command.command();
    }
  }
  return programMap;
}

}  // namespace

ProgramInstance::ProgramInstance(Program* p)
    : program_(p), programMap_(makeProgramMap(*p)) {
}

void ProgramInstance::getAllCommands(juce::Array<CommandID>& commands) {
  for (auto& mapEntry: programMap_)
    commands.add(mapEntry.first);
}

void ProgramInstance::getCommandInfo(CommandID command,
                                     ApplicationCommandInfo& info) {
  try {
    const Command& command = programMap_.at(info.commandID);
    const Description& desc = command.desc();
    int flags = command.flags();
    if (hasProperty(*program_, command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*program_, command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    info.setInfo(desc.name(), desc.full(0), command.category(), flags);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "getCommandInfo out of range " << info.commandID;
  }
}

bool ProgramInstance::perform(const InvocationInfo& info) {
  try {
	  return program_->perform(info, programMap_.at(info.commandID));
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Tried to invoke out of range command " << info.commandID;
    return false;
  }
}

}  // namespace app
}  // namespace rec
