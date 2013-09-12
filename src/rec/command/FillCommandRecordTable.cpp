#include "rec/command/FillCommandRecordTable.h"

#include "rec/command/CommandData.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/ID.h"
#include "rec/command/TickedDataSetter.h"
#include "rec/data/Data.h"
#include "rec/program/JuceModel.h"
#include "rec/util/thread/MakeCallback.h"
#include "rec/slow/commands/SlowProgram.h"

namespace rec {
namespace command {

namespace {

void fillSingleCommand(const CommandData& data, CommandRecordTable* table,
                       const Command& cmd) {
  const CommandID t = cmd.command();
  CommandRecord* cr = table->find(t);
  if (!cr) {
    DCHECK(cmd.has_setter()) << cmd.ShortDebugString();
    cr = table->create(t);
    const data::Address& a = cmd.setter().address();
    Scope s = scope(cmd.setter().is_global());
    cr->setter_.reset(new TickedDataSetter(cr->getInfo(), cmd, a, s));
    cr->callback_ = thread::methodCallback(cr->setter_.get(),
                                           &CommandItemSetter::execute);
  }
  DCHECK(!cr->command_) << cr->command_->ShortDebugString();
  cr->command_.reset(new Command(cmd));
}

Command* indexCommand(const Command& cmd, int index) {
  ptr<Command> command(new Command);
  command->set_command(cmd.command());
  command->set_index(index);
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

void fillRepeatingCommand(CommandRecordTable* table, const Command& cmd) {
  int len = cmd.desc().menu_size();
  ID begin(cmd.command());
  ID end = begin + len;
  for (ID i = begin; i != end; ++i) {
    if (CommandRecord* cr = table->find(i)) {
      DCHECK(!cr->command_) << cr->command_->ShortDebugString();
      cr->command_.reset(indexCommand(cmd, i - begin));
    } else {
      LOG(DFATAL) << "No repeat for " << i;
    }
  }
}

}  // namespace

void fillCommandRecordTable(const CommandData& data,
                            CommandRecordTable* table) {
 data.addCallbacks(table);
  const Commands& commands = data.allCommands();
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& cmd = commands.command(i);
    if (cmd.has_index())
      fillRepeatingCommand(table, cmd);
    else
      fillSingleCommand(data, table, cmd);
  }
  table->fillAllCommands();
}

}  // namespace command
}  // namespace rec
