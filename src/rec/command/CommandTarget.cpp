#include "rec/command/CommandTarget.h"

#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/program/JuceModel.h"
#include "rec/program/Program.h"

namespace rec {
namespace command {

void CommandTarget::getAllCommands(juce::Array<CommandID>& commands) {
  commandRecordTable()->getAllCommands(&commands);
}

void CommandTarget::getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
  Lock l(lock_);
  CommandRecord* cr = commandRecordTable()->find(id);
  if (!cr) {
    LOG(DFATAL) << "Couldn't get command info for id " << ID(id);
    return;
  }
  info = *(cr->getInfo());

  if (!info.shortName.isNotEmpty()) {
    LOG(ERROR) << "No name for " << program::getProgram()->commandName(id);
    info.shortName = "ERROR";
  }
}

bool CommandTarget::perform(const InvocationInfo& invocation) {
  Lock l(lock_);
  if (enable_ == DISABLE)
    return true;

  ID id = invocation.commandID;
  program::getProgram()->beforeCommand(id);

  CommandRecord* cr = commandRecordTable()->find(id);
  bool success = false;
  if (!cr)
    LOG(DFATAL) << "No record for " << id;
  else if (!cr->callback_)
    LOG(DFATAL) << "No callback for " << id;
  else
    success = true;

  if (success)
    (*(cr->callback_))();

  return success;
}

void CommandTarget::operator()(ID id) {
  if (!program::juceModel()->invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << id;
}

void CommandTarget::operator()(Enable enable) {
  Lock l(lock_);
  enable_ = enable;
}

}  // namespace command
}  // namespace rec
