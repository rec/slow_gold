#include "rec/slow/Target.h"

#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::command;

namespace rec {
namespace slow {

bool Target::perform(const InvocationInfo& invocation) {
  CommandID id = invocation.commandID;
	if (id != Command::ABOUT_THIS_PROGRAM && window())
    thread::callAsync(window(), &app::Window::stopAboutWindow);

  Lock l(lock_);
  return (enable_ == DISABLE) || commandRecordTable()->perform(id);
}

void Target::operator()(CommandID id) {
  if (!applicationCommandManager()->invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << CommandIDEncoder::commandIDName(id);
}

void Target::operator()(Enable enable) {
  Lock l(lock_);
  enable_ = enable;
}

}  // namespace slow
}  // namespace rec

