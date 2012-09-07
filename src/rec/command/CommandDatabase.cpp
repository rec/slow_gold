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

class CommandDatabase {
 public:
  CommandDatabase(CommandRecordTable* table, const CommandData& data)
      : table_(table), data_(data) {
  }

  void fill() {
    data_.addCallbacks(table_);
    fillFromCommands();
    removeEmptiesAndFillCommandInfo();
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
      DCHECK(cmd.has_is_global_setter() || cmd.has_is_setter())
        << cmd.ShortDebugString();
      cr = table_->find(t, true);
      addSetter(cmd, cr);
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
      if (CommandRecord* cr = table_->find(i, false)) {
        ptr<Command> newCmd(new Command);
        newCmd->set_type(t);
        int index = i - begin;
        newCmd->set_index(index + CommandIDEncoder::FIRST);
        newCmd->set_category(cmd.category());
        newCmd->mutable_desc()->add_menu(cmd.desc().menu(index));
        newCmd->mutable_desc()->add_full(cmd.desc().full(index));
        if (index < cmd.keypress_size()) {
          const string& kp = cmd.keypress(index);
            if (!kp.empty())
              newCmd->add_keypress(kp);
        }
        cr->command_.swap(newCmd);
      } else {
        LOG(DFATAL) << "No repeated record for " << commandName(t);
      }
    }
  }

  void addSetter(const Command& c, CommandRecord* cr) {
    const data::Address& a = c.address();
    Listener<None>* ls = data_.getMenuUpdateListener();
    Scope s = scope(c.is_global_setter());
    cr->setter_.reset(new TickedDataSetter(&cr->info_, ls, c, a, s));
    cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                               &CommandItemSetter::execute));
  }

  void fillOneCommandInfo(CommandID id, CommandRecord* cr) {
    const Description& desc = cr->command_->desc();
    String name = Trans(desc.full(0));
    String category = str(cr->command_->category());
    bool hasInfo = desc.menu_size() && name.length();

    if (hasInfo) {
      int flags = 0;
      if (category == "" || category == "(None)") {
        DCHECK_NE(category, "");
        flags += ApplicationCommandInfo::hiddenFromKeyEditor;
      }

      cr->info_.setInfo(Trans(desc.menu(0)), name, category, flags);
    } else {
      LOG(DFATAL) << "No command " << commandName(id)
                 << ", " << desc.menu_size()
                 << ", " << name.length()
                 << cr->command_->ShortDebugString();
    }
  }

  void removeEmptiesAndFillCommandInfo() {
    CommandRecordTable::iterator i;
    for (i = table_->begin(); i != table_->end(); ++i) {
      CommandID id = i->first;
      CommandRecord* cr = i->second;
      if (!cr->command_)
        LOG(DFATAL) << "Command not in Command.def " << commandName(id);
      else if (!cr->callback_)
        LOG(DFATAL) << "Empty callback " << commandName(id);
      else {
        fillOneCommandInfo(id, cr);
        continue;
      }
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
