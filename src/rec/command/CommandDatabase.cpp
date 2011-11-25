#include "rec/command/CommandDatabase.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/data/Data.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

namespace {

class CommandDatabase {
 public:
  CommandDatabase(CommandRecordTable* table, const CommandData& data,
                  Listener<None>* listener)
      : table_(table), data_(data), listener_(listener) {
  }

  void fill() {
    insertSingle();
    insertRepeated();
    insertSetters();
    mergeKeyPresses();
    mergeDescriptions();
    removeEmpties();
  }

 private:
  enum MergeType {INSERT, MERGE};

  void addTo(MergeType type, const Command& cmd, CommandID id = 0) {
    if (!id)
      id = CommandIDEncoder::toCommandID(cmd);

    CommandRecord* cr(find(table_, id));
    if (type == INSERT) {
      if (cr->command_)
        LOG(DFATAL) << "Can't insert " << commandName(id);
      else {
        DLOG(INFO) << "Inserting " << commandName(id);
        cr->command_.reset(new Command(cmd));
      }
    } else {
      if (cr->command_) {
        DLOG(INFO) << "Merging " << commandName(id);
        cr->command_->MergeFrom(cmd);
      } else {
        LOG(DFATAL) << "Can't merge " << commandName(id);
      }
    }
  }

  void merge(const Command& cmd, CommandID id = 0) {
    addTo(MERGE, cmd, id);
  }

  void insert(const Command& cmd, CommandID id = 0) {
    addTo(INSERT, cmd, id);
  }

  void insert(const Commands& commands) {
    for (int i = 0; i < commands.command_size(); ++i)
      insert(commands.command(i));
  }

  void mergeDescription(const Command& command) {
    CommandRecord* cr = find(table_, command.type(), false);
    if (cr) {
      DCHECK(cr->command_);
      if (cr->command_)
        cr->command_->MergeFrom(command);
      return;
    }

    static const char* LOWER[] = {" the first", " the previous", " the current",
                                  " the next", " the last"};
    static const char* CAP[] = {" First", " Previous", " Current", " Next",
                                " Last"};

    const String menu = command.desc().menu_size() ?
        str(command.desc().menu(0)) : String();
    const String full = str(command.desc().full());

    CommandID c = Command::BANK_SIZE * command.type();
    for (int i = 0; i <= CommandIDEncoder::LAST - CommandIDEncoder::FIRST; ++i, ++c) {
      CommandRecord* cr = find(table_, c);
      if (!cr->command_) {
        LOG(DFATAL) << "Couldn't find position " << i
                   << " CommandID " << c
                   << " cmd: " << command.ShortDebugString();
        return;
      }
      Description* desc = cr->command_->mutable_desc();
      desc->add_menu(str(String::formatted(menu, CAP[i], "")));
      desc->set_full(str(String::formatted(full, LOWER[i], "")));
    }

    for (int i = 0; ; ++i, ++c) {
      CommandRecord* cr = find(table_, c, false);
      if (!cr)
        return;

      DCHECK(cr->command_);
      if (!cr->command_) {
        LOG(DFATAL) << "Can't merge desc: " << commandName(c);
        continue;
      }

      String n = " " + String(i + 1);
      const char* s = n.toUTF8();
      Description* desc = cr->command_->mutable_desc();
      desc->add_menu(str(String::formatted(menu, "", s)));
      desc->set_full(str(String::formatted(full, "", s)));
    }
  }

  void insertSingle() {
    insert(data_.commands());
  }

  void insertRepeated() {
    for (int i = 0; i < data_.repeated().command_size(); ++i) {
      const Command& command = data_.repeated().command(i);
      Command c = command;

      // Insert each specific subcommand.
      for (int j = CommandIDEncoder::FIRST; j < command.index(); ++j) {
        c.set_index(j);
        insert(c, CommandIDEncoder::toCommandID(j, command.type()));
      }
    }
  }

  void insertSetters() {
    insert(data_.setters());

    for (int i = 0; i < data_.setters().command_size(); ++i) {
      const Command& cmd = data_.setters().command(i);
      int id = cmd.type();
      CommandRecord* cr = find(table_, id);

      if (cr->setter_)
        LOG(DFATAL) << "Duplicate setter " << commandName(id);

      using slow::GuiSettings;
      using audio::stretch::Stretch;

      const data::Address& a = cmd.address();
      if (id == Command::TOGGLE_GRID_DISPLAY) {
        cr->setter_.reset(new CommandDataSetter<GuiSettings>(listener_, cmd,
                                                             a, true));

      } else if (id == Command::TOGGLE_STRETCH_ENABLE) {
        cr->setter_.reset(new CommandDataSetter<Stretch>(listener_, cmd,
                                                         a, false));

      } else {
        LOG(DFATAL) << "Didn't understand " << commandName(id);
        continue;
      }

      if (cr->callback_)
        LOG(DFATAL) << "Duplicate callback " << commandName(id);

      cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                                 &CommandItemSetter::execute));
      DLOG(INFO) << "Adding callback for " << commandName(id);
    }
  }

  void mergeKeyPresses() {
    Commands kp = data_.keyPresses(access_);
    for (int i = 0; i < kp.command_size(); ++i)
      merge(kp.command(i));
  }

  void mergeDescriptions() {
    const Commands& desc = data_.descriptions(access_);
    for (int i = 0; i < desc.command_size(); ++i)
      mergeDescription(desc.command(i));
  }

  void removeEmpties() {
    std::vector<CommandID> empties;
    CommandRecordTable::iterator i;
    for (i = table_->begin(); i != table_->end(); ++i) {
      string error;
      if (!i->second->command_) {
        error = "No command";
      } else {
        const Description& desc = i->second->command_->desc();
        if (!(desc.menu().size() && desc.full().size()))
          error = "missing description for " + i->second->command_->ShortDebugString();
      }
      if (!error.empty()) {
        empties.push_back(i->first);
        LOG(DFATAL) << "Removing " << commandName(i->first)
                   << " because " << error;
        CHECK(false);
      }
    }

    for (uint i = 0; i < empties.size(); ++i)
      table_->erase(empties[i]);
  }

  CommandRecordTable* table_;
  const CommandData& data_;
  Listener<None>* listener_;
  Access access_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandDatabase);
};

}  // namespace

void fillCommandRecordTable(CommandRecordTable* table, const CommandData& data,
                            Listener<None>* listener) {
  CommandDatabase(table, data, listener).fill();
}

}  // namespace command
}  // namespace rec
