#include "rec/command/CommandRecord.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

void CommandRecord::fillInfo() {
	if (!command_)
  	return;

  CommandID id = info_.commandID;
  if (!callback_)
    LOG(DFATAL) << "Empty callback " << CommandIDEncoder::commandIDName(id);

  const Description& desc = command_->desc();
  String name = Trans(desc.full(0));
  String category = str(command_->category());
  bool hasInfo = desc.menu_size() && name.length();

  if (hasInfo) {
    int flags = 0;
    if (category == "" || category == "(None)") {
      DCHECK_NE(category, "");
      flags += ApplicationCommandInfo::hiddenFromKeyEditor;
    }

    info_.setInfo(Trans(desc.menu(0)), name, category, flags);
  } else {
    LOG(DFATAL) << "No command " << CommandIDEncoder::commandIDName(id)
               << ", " << desc.menu_size()
               << ", " << name.length()
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
