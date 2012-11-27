#include "rec/command/CommandTarget.h"

#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/Target.h"

namespace rec {
namespace command {

void CommandTarget::getAllCommands(juce::Array<CommandID>& commands) {
  commandRecordTable()->getAllCommands(&commands);
}

void CommandTarget::getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
  CommandRecord* cr = commandRecordTable()->find(id);
  if (!cr) {
    LOG(DFATAL) << "Couldn't get command info for id "
                << CommandIDEncoder::commandIDName(id);
    return;
  }
  info = *(cr->getInfo());

  if (!info.shortName.isNotEmpty())
    LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id);
}

bool CommandTarget::perform(const InvocationInfo& info) {
  return instance_->target_->perform(info);
}

}  // namespace command
}  // namespace rec

