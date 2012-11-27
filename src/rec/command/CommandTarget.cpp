#include "rec/command/CommandTarget.h"

#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace command {

void CommandTarget::getAllCommands(juce::Array<CommandID>& commands) {
  commandRecordTable()->getAllCommands(&commands);
}

void CommandTarget::getCommandInfo(CommandID id, ApplicationCommandInfo& info) {
  Lock l(lock_);
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

bool CommandTarget::perform(const InvocationInfo& invocation) {
  Lock l(lock_);
  if (enable_ == DISABLE)
    return true;

  CommandID id = invocation.commandID;
	if (id != Command::ABOUT_THIS_PROGRAM && window())
    thread::callAsync(window(), &app::Window::stopAboutWindow);

  CommandRecord* cr = commandRecordTable()->find(id);
  bool success = false;
  if (!cr)
    LOG(DFATAL) << "No record for " << CommandIDEncoder::commandIDName(id);
  else if (!cr->callback_)
    LOG(DFATAL) << "No callback for " << CommandIDEncoder::commandIDName(id);
  else
    success = true;

  if (success)
    (*(cr->callback_))();

  return success;
}

void CommandTarget::operator()(CommandID id) {
  if (!applicationCommandManager()->invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << CommandIDEncoder::commandIDName(id);
}

void CommandTarget::operator()(Enable enable) {
  Lock l(lock_);
  enable_ = enable;
}

}  // namespace command
}  // namespace rec

