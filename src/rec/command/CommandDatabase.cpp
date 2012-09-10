#include "rec/command/CommandDatabase.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/command/TickedDataSetter.h"
#include "rec/data/Data.h"
#include "rec/util/thread/MakeCallback.h"
#include "rec/widget/waveform/Waveform.pb.h"

// #define OLD_COMMAND_FILE

namespace rec {
namespace command {

namespace {

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


class CommandDatabase {
 public:
  CommandDatabase(CommandRecordTable* table, const CommandData& data)
      : table_(table), data_(data) {
  }

  void fill() {
    data_.addCallbacks(table_);
    fillFromCommands();
    table_->fillCommandInfo();
  }

 private:
  void fillFromCommands() {
    const Commands& commands = data_.allCommands();
    for (int i = 0; i < commands.command_size(); ++i) {
      const Command& cmd = commands.command(i);
      if (cmd.has_start_index())
        fillRepeatingCommand(cmd);
      else
        fillSingleCommand(cmd);
    }
  }

  void fillSingleCommand(const Command& cmd) {
    const Command::Type t = cmd.type();
    CommandRecord* cr = table_->find(t, false);
    if (!cr) {
      DCHECK(cmd.has_setter()) << cmd.ShortDebugString();
      cr = table_->find(t, true);
      const data::Address& a = cmd.setter().address();
      Listener<None>* ls = data_.getMenuUpdateListener();
      Scope s = scope(cmd.setter().is_global());
      cr->setter_.reset(new TickedDataSetter(&cr->info_, ls, cmd, a, s));
      cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                                 &CommandItemSetter::execute));
    }
    cr->command_.reset(new Command(cmd));
  }

  void fillRepeatingCommand(const Command& cmd) {
    const Command::Type t = cmd.type();
    int len = cmd.desc().menu_size();
    DCHECK_EQ(len, cmd.desc().full_size()) << cmd.ShortDebugString();
    CommandID begin = CommandIDEncoder::toCommandID(cmd.start_index(), t);
    CommandID end = begin + len;
    for (CommandID i = begin; i != end; ++i) {
      if (CommandRecord* cr = table_->find(i, false))
        cr->command_.reset(indexCommand(cmd, i - begin));
      else
        LOG(DFATAL) << "No repeat for " << CommandIDEncoder::commandIDName(t);
    }
  }

 private:
  CommandRecordTable* table_;
  const CommandData& data_;
  Access access_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandDatabase);
};

}  // namespace

void fillCommandRecordTable(CommandRecordTable* table, const CommandData& data) {
  CommandDatabase(table, data).fill();
}

}  // namespace command
}  // namespace rec
