#include "rec/slow/Target.h"

#include "rec/audio/Device.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/CommandTarget.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/data/DataOps.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/MethodListener.h"

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

void Target::addCommandItem(PopupMenu* menu, CommandID id, bool enable,
                            const String& name, int flags) {
  commandRecordTable()->fillCommandInfo(id, name, flags,
                                        enable ? ENABLE : DISABLE);
  menu->addCommandItem(applicationCommandManager(), id);
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

