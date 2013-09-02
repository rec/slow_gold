#include "rec/command/CommandRecord.h"
#include "rec/slow/commands/SlowCommand.pb.h"

namespace rec {
namespace command {

void CommandRecord::fillInfo() {
	if (!command_)
  	return;

  ID id = info_.commandID;
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
      CommandID t = id.get();
      if (t == slow::SlowCommand::TOGGLE_WHOLE_SONG_LOOP || t == slow::SlowCommand::RECENT_FILES)
        name = info_.shortName;
    }

    info_.setInfo(name, fullName, category, flags);
  } else {
    LOG(DFATAL) << "No command " << id
               << ", " << desc.menu_size()
               << ", " << fullName.length()
               << command_->ShortDebugString();
  }
}

Command* indexCommand(const Command& cmd, int index) {
  ptr<Command> command(new Command);
  command->set_command(cmd.command());
  command->set_index(index + ID::FIRST);
  command->set_category(cmd.category());
  if (cmd.desc().menu_size() > index)
    command->mutable_desc()->add_menu(cmd.desc().menu(index));
  else
    DCHECK_GT(cmd.desc().menu_size(), index);
  if (cmd.desc().full_size() > index)
    command->mutable_desc()->add_full(cmd.desc().full(index));
  else
    DCHECK_GT(cmd.desc().full_size(), index);

  return command.release();
}

}  // namespace command
}  // namespace rec
