#include "rec/command/CommandRecord.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

ApplicationCommandInfo* CommandRecord::getInfo() {
  fillInfo();
  return &info_;
}

void CommandRecord::fillInfo() {
	if (!command_)
  	return;

  CommandID id = info_.commandID;
  if (!callback_)
    LOG(DFATAL) << "Empty callback " << CommandIDEncoder::commandIDName(id);

  const Description& desc = command_->desc();
  String fullName = Trans(desc.full(0));
  String category = str(command_->category());
  bool hasInfo = desc.menu_size() && fullName.length();

  if (hasInfo) {
    int flags = 0;
    DCHECK_NE(category, "");
    if (category == "(None)")
      flags += ApplicationCommandInfo::hiddenFromKeyEditor;

    if (info_.flags & ApplicationCommandInfo::isTicked)
      flags += ApplicationCommandInfo::isTicked;

    // Hack to deal with RECENT_FILES translation issues.
    // TODO: fix this - and why isn't needed for the language menu?
    String name = Trans(desc.menu(0));
    if (info_.shortName.length()) {
      Command::Type t = CommandIDEncoder::getType(id);
      if (t == Command::TOGGLE_WHOLE_SONG_LOOP || t == Command::RECENT_FILES)
        name = info_.shortName;
    }

    info_.setInfo(name, fullName, category, flags);
  } else {
    LOG(DFATAL) << "No command " << CommandIDEncoder::commandIDName(id)
               << ", " << desc.menu_size()
               << ", " << fullName.length()
               << command_->ShortDebugString();
  }
}

Command* indexCommand(const Command& cmd, int index) {
  ptr<Command> command(new Command);
  command->set_type(cmd.type());
  command->set_index(index + CommandIDEncoder::FIRST);
  command->set_category(cmd.category());
  if (cmd.desc().menu_size() > index)
    command->mutable_desc()->add_menu(cmd.desc().menu(index));
  else
    DCHECK_GT(cmd.desc().menu_size(), index);
  if (cmd.desc().full_size() > index)
    command->mutable_desc()->add_full(cmd.desc().full(index));
  else
    DCHECK_GT(cmd.desc().full_size(), index);

  if (index < cmd.keypress_size()) {
    const string& kp = cmd.keypress(index);
      if (!kp.empty())
        command->add_keypress(kp);
  }
  return command.transfer();
}

}  // namespace command
}  // namespace rec
