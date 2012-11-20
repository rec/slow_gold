#include "rec/command/CommandDatabase.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/FillCommandRecordTable.h"
#include "rec/command/TickedDataSetter.h"
#include "rec/data/Data.h"
#include "rec/util/thread/MakeCallback.h"
#include "rec/widget/waveform/Waveform.pb.h"

namespace rec {
namespace command {

CommandDatabase::CommandDatabase(CommandRecordTable* table, const CommandData& data)
    : table_(table), data_(data) {
}

void CommandDatabase::fill() {
  data_.addCallbacks(table_);
  const Commands& commands = data_.allCommands();
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& cmd = commands.command(i);
    if (cmd.has_start_index())
      fillRepeatingCommand(cmd);
    else
      fillSingleCommand(cmd);
  }
}

void CommandDatabase::fillSingleCommand(const Command& cmd) {
  const Command::Type t = cmd.type();
  CommandRecord* cr = table_->find(t);
  if (!cr) {
    DCHECK(cmd.has_setter()) << cmd.ShortDebugString();
    cr = table_->create(t);
    const data::Address& a = cmd.setter().address();
    Listener<None>* ls = data_.getMenuUpdateListener();
    Scope s = scope(cmd.setter().is_global());
    cr->setter_.reset(new TickedDataSetter(cr->getInfo(), ls, cmd, a, s));
    cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                               &CommandItemSetter::execute));
  }
  DCHECK(!cr->command_) << cr->command_->ShortDebugString();
  cr->command_.reset(new Command(cmd));
}

void CommandDatabase::fillRepeatingCommand(const Command& cmd) {
  const Command::Type t = cmd.type();
  int len = cmd.desc().menu_size();
  DCHECK_EQ(len, cmd.desc().full_size()) << cmd.ShortDebugString();
  CommandID begin = CommandIDEncoder::toCommandID(cmd.start_index(), t);
  CommandID end = begin + len;
  for (CommandID i = begin; i != end; ++i) {
    if (CommandRecord* cr = table_->find(i)) {
      DCHECK(!cr->command_) << cr->command_->ShortDebugString();
      cr->command_.reset(indexCommand(cmd, i - begin));
    } else {
      LOG(DFATAL) << "No repeat for " << CommandIDEncoder::commandIDName(t);
    }
  }
}

}  // namespace command
}  // namespace rec
