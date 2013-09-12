#include "rec/command/CommandRecord.h"
#include "rec/slow/commands/SlowCommand.pb.h"

namespace rec {
namespace command {

void CommandRecord::fillInfo() {
	if (!command_) {
    LOG(ERROR) << "No command for " << info_.commandID;
  	return;
  }

  CommandID id = info_.commandID;
  if (!callback_)
    LOG(DFATAL) << "Empty callback " << id;

  const Description& desc = command_->desc();
  String fullName = Trans(desc.full(0));
  String category = str(command_->category());
  bool hasInfo = desc.menu_size() && fullName.length();

  if (hasInfo) {
    int flags = 0;
    if (category == "" || category == "(None)")
      flags += ApplicationCommandInfo::hiddenFromKeyEditor;

    if (info_.flags & ApplicationCommandInfo::isTicked)
      flags += ApplicationCommandInfo::isTicked;

    // Hack to deal with RECENT_FILES translation issues.
    // TODO: fix this - and why isn't needed for the language menu?
    String name = Trans(desc.menu(0));
    if (info_.shortName.length()) {
      if (id == slow::SlowCommand::TOGGLE_WHOLE_SONG_LOOP ||
          id == slow::SlowCommand::RECENT_FILES) {
        name = info_.shortName;
      }
    }

    info_.setInfo(name, fullName, category, flags);
  } else {
    LOG(DFATAL) << "No command " << id
               << ", " << desc.menu_size()
               << ", " << fullName.length()
               << command_->ShortDebugString();
  }
}

}  // namespace command
}  // namespace rec
