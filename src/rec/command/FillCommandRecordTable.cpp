#include "rec/command/FillCommandRecordTable.h"

#include "rec/command/CommandData.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/ID.h"
#include "rec/command/TickedDataSetter.h"
#include "rec/data/Data.h"
#include "rec/util/thread/MakeCallback.h"

namespace rec {
namespace command {

namespace {

void fillSingleCommand(const CommandData& data, CommandRecordTable* table,
                       const Command& cmd) {
  const Command::Type t = cmd.type();
  CommandRecord* cr = table->find(t);
  if (!cr) {
    DCHECK(cmd.has_setter()) << cmd.ShortDebugString();
    cr = table->create(t);
    const data::Address& a = cmd.setter().address();
    Listener<None>* ls = data.getMenuUpdateListener();
    Scope s = scope(cmd.setter().is_global());
    cr->setter_.reset(new TickedDataSetter(cr->getInfo(), ls, cmd, a, s));
    cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                               &CommandItemSetter::execute));
  }
  DCHECK(!cr->command_) << cr->command_->ShortDebugString();
  cr->command_.reset(new Command(cmd));
}

void fillRepeatingCommand(CommandRecordTable* table, const Command& cmd) {
  int len = cmd.desc().menu_size();
  DCHECK_EQ(len, cmd.desc().full_size()) << cmd.ShortDebugString();
  ID begin = ID(cmd.type(), cmd.start_index());
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
    if (cmd.has_start_index())
      fillRepeatingCommand(table, cmd);
    else
      fillSingleCommand(data, table, cmd);
  }
  table->fillAllCommands();
}

}  // namespace command
}  // namespace rec
