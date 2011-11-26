#include "rec/command/CommandDatabase.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/data/Data.h"
#include "rec/widget/waveform/Waveform.pb.h"

namespace rec {
namespace command {

namespace {

class CommandDatabase {
 public:
  CommandDatabase(CommandRecordTable* table, const CommandData& data)
      : table_(table), data_(data) {
  }

  void fill() {
    insertSingle();
    insertRepeated();
    insertSetters();
    mergeKeyPresses();
    mergeDescriptions();
    removeEmptiesAndFillCommandInfo();
  }

 private:
  enum MergeType {INSERT, MERGE};

  void addTo(MergeType type, const Command& cmd, CommandID id = 0) {
    if (!id)
      id = CommandIDEncoder::toCommandID(cmd);

    CommandRecord* cr(table_->find(id));
    if (type == INSERT) {
      if (cr->command_) {
        LOG(DFATAL) << "Can't insert " << commandName(id);
      } else {
        // DLOG(INFO) << "Inserting " << commandName(id);
        cr->command_.reset(new Command(cmd));

      }
    } else {
      if (cr->command_) {
        // DLOG(INFO) << "Merging " << commandName(id);
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
    // DLOG(INFO) << "Starting to merge " << commandName(command.type());
    CommandRecord* cr = table_->find(command.type(), false);
    if (cr) {
      DCHECK(cr->command_) << commandName(command.type());
      if (cr->command_) {
        Command before(*cr->command_);
        cr->command_->MergeFrom(command);
        // DLOG(INFO) << "Merge!! " << before.ShortDebugString()
        //           << "  |||  " << command.ShortDebugString()
        //         << "  |||  " << cr->command_->ShortDebugString() ;
      }
      return;
    }

    static const char* LOWER[] = {" the first", " the previous", " the current",
                                  " the next", " the last"};
    static const char* CAP[] = {" First", " Previous", " Current", " Next",
                                " Last"};

    const String menu = command.desc().menu_size() ?
        str(command.desc().menu(0)) : String();
    const String full = str(command.desc().full());

    CommandID type = command.type();
    CommandID c = Command::BANK_SIZE * type;
    for (int i = 0; i <= CommandIDEncoder::LAST - CommandIDEncoder::FIRST; ++i, ++c) {
      if (type != Command::RECENT_FILES) {
        CommandRecord* cr = table_->find(c);
        if (!cr->command_) {
          LOG(DFATAL) << "Couldn't find position " << i
                     << " Command " << commandName(c)
                     << " cmd: " << command.ShortDebugString();
          return;
        }
        Description* desc = cr->command_->mutable_desc();
        desc->add_menu(str(String::formatted(menu, CAP[i], "")));
        desc->set_full(str(String::formatted(full, LOWER[i], "")));
      }
    }

    for (int i = 0; ; ++i, ++c) {
      CommandRecord* cr = table_->find(c, false);
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
      int j = command.has_start_index() ? command.start_index() :
        CommandIDEncoder::FIRST;
      // Insert each specific subcommand.
      for (; j < command.index(); ++j) {
        c.set_index(j);
        insert(c, CommandIDEncoder::toCommandID(j, command.type()));
      }
    }
  }

  void insertSetters() {
    using widget::waveform::WaveformProto;
    using audio::stretch::Stretch;

    for (int i = 0; i < data_.setters().command_size(); ++i) {
      int id = data_.setters().command(i).type();
      CommandRecord* cr = table_->find(id);
      if (cr->setter_) {
        LOG(DFATAL) << "Duplicate setter " << commandName(id);
        continue;
      }

      if (cr->callback_) {
        LOG(DFATAL) << "Duplicate callback " << commandName(id);
        continue;
      }

      if (cr->command_) {
        LOG(DFATAL) << "Duplicate command " << commandName(id)
                    << ", " << cr->command_->ShortDebugString();
        continue;
      }

      cr->command_.reset(new Command(data_.setters().command(i)));
      const Command& c = *cr->command_;

      const data::Address& a = c.address();
      Listener<None>* ls = data_.getMenuUpdateListener();
      if (id == Command::TOGGLE_GRID_DISPLAY)
        cr->setter_.reset(new CommandDataSetter<WaveformProto>(ls, c, a, true));
      else if (id == Command::TOGGLE_STRETCH_ENABLE)
        cr->setter_.reset(new CommandDataSetter<Stretch>(ls, c, a, false));

      if (!cr->setter_) {
        LOG(DFATAL) << "Didn't understand " << commandName(id);
        continue;
      }

      cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                                 &CommandItemSetter::execute));
      // DLOG(INFO) << "Adding callback for " << commandName(id);
    }
  }

  void mergeKeyPresses() {
    Commands kp = data_.keyPresses(access_);
    for (int i = 0; i < kp.command_size(); ++i) {
      // DLOG(INFO) << "Merging keypresses " << commandName(kp.command(i).type());
      merge(kp.command(i));
    }
  }

  void mergeDescriptions() {
    const Commands& desc = data_.descriptions(access_);
    for (int i = 0; i < desc.command_size(); ++i)
      mergeDescription(desc.command(i));
  }

  void fillOneCommandInfo(CommandID id, CommandRecord* cr) {
    const Description& desc = cr->command_->desc();
    String name = str(desc.full());
    String category = str(cr->command_->category());
    bool hasInfo = desc.menu_size() && name.length();

    DCHECK(hasInfo) << "no command " << desc.menu_size() << ", " << name.length();
    if (hasInfo) {
      cr->info_.reset(new ApplicationCommandInfo(id));
      int flags = 0;
      if (category == "" || category == "(None)")
        flags = ApplicationCommandInfo::hiddenFromKeyEditor;
      cr->info_->setInfo(str(desc.menu(0)), name, category, flags);
    }
  }

  void removeEmptiesAndFillCommandInfo() {
    std::vector<CommandID> empties;
    CommandRecordTable::iterator i;
    for (i = table_->begin(); i != table_->end(); ++i) {
      CommandID id = i->first;
      CommandRecord* cr = i->second;
      if (!cr->command_)
        LOG(DFATAL) << "No command " << commandName(id);
      else if (!cr->callback_)
        LOG(DFATAL) << "No callback " << commandName(id);
      else
        fillOneCommandInfo(id, cr);

      if (!cr->info_)
        empties.push_back(id);
    }

    for (uint i = 0; i < empties.size(); ++i)
      table_->erase(empties[i]);
  }


  CommandRecordTable* table_;
  const CommandData& data_;
  Access access_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandDatabase);
};


}  // namespace

void fillCommandRecordTable(CommandRecordTable* table, const CommandData& data) {
  data.addCallbacks(table);
  CommandDatabase(table, data).fill();
}

}  // namespace command
}  // namespace rec
