#include "rec/command/CommandDatabase.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TickedDataSetter.h"
#include "rec/data/Data.h"
#include "rec/util/thread/MakeCallback.h"
#include "rec/widget/waveform/Waveform.pb.h"

#define SINGLE_COMMAND_FILE

namespace rec {
namespace command {

namespace {

#ifdef JUCE_MAC
struct CompareCommandIds {
  static string toString(CommandID x) {
    return Command::Type_Name(static_cast<Command::Type>(x));
  }

  bool operator()(CommandID x, CommandID y) {
    return toString(x) < toString(y);
  }
};
#endif

class CommandDatabase {
 public:
  CommandDatabase(CommandRecordTable* table, const CommandData& data)
      : table_(table), data_(data) {
  }

  void fill() {
    data_.addCallbacks(table_);

#ifdef SINGLE_COMMAND_FILE
    fillFromCommands();
#else
    fillFromTable();
#if JUCE_DEBUG && JUCE_MAC
    rawMergeAndPrint();
#endif
#endif
    removeEmptiesAndFillCommandInfo();

  }

 private:
  void fillFromCommands() {
    const Commands& commands = data_.allCommands();
    for (int i = 0; i < commands.command_size(); ++i)
      fillOneCommand(commands.command(i));
  }

  void fillOneCommand(const Command& cmd) {
    if (cmd.has_start_index())
      fillRepeatingCommand(cmd);
    else
      fillSingleCommand(cmd);
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
        newCmd->set_type(t);  // TODO:  is this right?!?
        int index = i - begin;
        newCmd->set_index(index);  // TODO:  is this right?!?
        newCmd->set_category(cmd.category());
        newCmd->mutable_desc()->add_menu(cmd.desc().menu(index));
        newCmd->mutable_desc()->add_full(cmd.desc().full(index));
        if (index < cmd.keypress_size()) {
          const string& kp = cmd.keypress(index);
            if (!kp.empty())
              newCmd->add_keypress(kp);
        }
        // DLOG(INFO) << newCmd->ShortDebugString();
        cr->command_.swap(newCmd);
      } else {
        LOG(DFATAL) << "No repeated record for " << commandName(t);
      }
    }
  }

  void fillFromTable() {
    insertSingle();
    insertRepeated();
    insertSetters();
    mergeKeyPresses();
    mergeDescriptions();
  }

#if JUCE_MAC
  typedef std::map<CommandID, Command*, CompareCommandIds> Table;

  void rawMerge(Table* table, Commands commands) {
    for (int i = 0; i < commands.command_size(); ++i) {
      const Command& c = commands.command(i);
      Table::iterator j = table->find(c.type());
      if (j == table->end())
        table->insert(std::make_pair(c.type(), new Command(c)));
      else
        j->second->MergeFrom(c);
    }
  }

  void rawMergeAndPrint() {
    Table table;

    rawMerge(&table, data_.commands());
    rawMerge(&table, data_.repeated());
    rawMerge(&table, data_.setters());
    rawMerge(&table, data_.keyPresses(access_));
    rawMerge(&table, data_.descriptions(access_));

    Commands commands;
    for (Table::iterator i = table.begin(); i != table.end(); ++i)
      commands.add_command()->CopyFrom(*i->second);
    String commandString(str(commands.DebugString()));

    File out("/tmp/records.txt");
    out.deleteFile();
    juce::FileOutputStream(out).writeText(commandString, false, false);
  }
#endif

  enum MergeType {INSERT, MERGE};

  void addTo(MergeType type, const Command& cmd, CommandID id = 0) {
    if (!id)
      id = CommandIDEncoder::toCommandID(cmd);

    CommandRecord* cr(table_->find(id));
    if (type == INSERT) {
      if (cr->command_)
        LOG(DFATAL) << "Can't insert " << commandName(id);
      else
        cr->command_.reset(new Command(cmd));

    } else {
      if (cr->command_)
        cr->command_->MergeFrom(cmd);
      else
        LOG(DFATAL) << "Can't merge " << commandName(id);
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
    CommandRecord* cr = table_->find(command.type(), false);
    if (cr) {
      DCHECK(cr->command_) << commandName(command.type());
      if (cr->command_)
        cr->command_->MergeFrom(command);
      return;
    }

    // If we get here, this is a repeated command!
    static const char* LOWER[] = {" the first", " the previous", " the current",
                                  " the next", " the last"};
    static const char* CAP[] = {" First", " Previous", " Current", " Next",
                                " Last"};

    const String menu = Trans(command.desc().menu_size() ?
                                  str(command.desc().menu(0)) : String());
    const String full = Trans(str(command.desc().full(0)));

    for (int i = 1; i < command.desc().menu_size(); ++i)
      Trans(str(command.desc().menu(i)));

    CommandID type = command.type();
    CommandID c = Command::BANK_SIZE * type;
    for (int i = 0; i <= CommandIDEncoder::LAST - CommandIDEncoder::FIRST; ++i, ++c) {
      if (type != Command::RECENT_FILES && type != Command::SET_SAVE_FORMAT) {
        CommandRecord* cr = table_->find(c);
        if (!cr->command_) {
          LOG(DFATAL) << "Couldn't find position " << i
                     << " Command " << commandName(c)
                     << " cmd: " << command.ShortDebugString();
          return;
        }
        Description* desc = cr->command_->mutable_desc();
        desc->add_menu(str(String::formatted(menu, CAP[i], "")));
        string fl = str(String::formatted(full, LOWER[i], ""));
        if (desc->full_size())
          desc->set_full(0, fl);
        else
          desc->add_full(fl);
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
      string fl = str(String::formatted(full, "", s));
      if (desc->full_size())
        desc->set_full(0, fl);
      else
        desc->add_full(fl);
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
    using audio::Gain;

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
      addSetter(c, cr);
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

  void fillOneCommandInfo(CommandID id, CommandRecord* cr) {
    const Description& desc = cr->command_->desc();
    String name = str(desc.full(0));
    String category = str(cr->command_->category());
    bool hasInfo = desc.menu_size() && name.length();

    if (hasInfo) {
      int flags = 0;
      if (category == "" || category == "(None)") {
        DCHECK_NE(category, "");
        flags += ApplicationCommandInfo::hiddenFromKeyEditor;
      }

      cr->info_.setInfo(str(desc.menu(0)), name, category, flags);
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
#ifdef SINGLE_COMMAND_FILE
        LOG(ERROR) << "Command not in Command.def " << commandName(id);
#else
        LOG(DFATAL) << "Command not in Command.def " << commandName(id);
#endif
      else if (!cr->callback_)
#ifdef SINGLE_COMMAND_FILE
        LOG(ERROR) << "Empty callback " << commandName(id);
#else
        LOG(DFATAL) << "Empty callback " << commandName(id);
#endif
      else {
        fillOneCommandInfo(id, cr);
        continue;
      }
    }
  }


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
