#include "rec/command/CommandDatabase.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/data/CommandData.h"
#include "rec/data/Data.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

namespace {

enum MergeType {INSERT, MERGE};

void addTo(MergeType type, CommandRecordTable* table, const Command& cmd,
           CommandID id = 0) {
  if (!id)
    id = CommandIDEncoder::toCommandID(cmd);

  CommandRecord* cr(find(table, id));
  if (type == INSERT) {
    if (cr->command_)
      LOG(ERROR) << "Can't insert " << commandName(id);
    else {
      DLOG(INFO) << "Inserting " << commandName(id);
      cr->command_.reset(new Command(cmd));
    }
  } else {
    if (cr->command_) {
      DLOG(INFO) << "Merging " << commandName(id);
      cr->command_->MergeFrom(cmd);
    } else {
      LOG(ERROR) << "Can't merge " << commandName(id);
    }
  }
}

void merge(CommandRecordTable* table, const Command& cmd, CommandID id = 0) {
  addTo(MERGE, table, cmd, id);
}

void insert(CommandRecordTable* table, const Command& cmd, CommandID id = 0) {
  addTo(INSERT, table, cmd, id);
}

void insert(CommandRecordTable* table, const Commands& commands) {
  for (int i = 0; i < commands.command_size(); ++i)
    insert(table, commands.command(i));
}

void mergeDescription(CommandRecordTable* table, const Command& command) {
  CommandRecord* cr = find(table, command.type(), false);
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
    CommandRecord* cr = find(table, c);
    if (!cr->command_) {
      LOG(ERROR) << "Couldn't find position " << i
                 << " CommandID " << c
                 << " cmd: " << command.ShortDebugString();
      return;
    }
    Description* desc = cr->command_->mutable_desc();
    desc->add_menu(str(String::formatted(menu, CAP[i], "")));
    desc->set_full(str(String::formatted(full, LOWER[i], "")));
  }

  for (int i = 0; ; ++i, ++c) {
    CommandRecord* cr = find(table, c);
    if (!cr->command_) {
      // DLOG(INFO) << "Can't merge desc: " << commandName(c);
      // DCHECK(false);
      break;
    }

    String n = " " + String(i + 1);
    const char* s = n.toUTF8();
    Description* desc = cr->command_->mutable_desc();
    desc->add_menu(str(String::formatted(menu, "", s)));
    desc->set_full(str(String::formatted(full, "", s)));
  }
}

}  // namespace

void insertSingle(CommandRecordTable* table) {
  insert(table, commands());
}

void insertRepeated(CommandRecordTable* commands) {
  for (int i = 0; i < repeated().command_size(); ++i) {
    const Command& command = repeated().command(i);
    Command c = command;

    // Insert each specific subcommand.
    for (int j = CommandIDEncoder::FIRST; j < command.index(); ++j) {
      c.set_index(j);
      insert(commands, c, CommandIDEncoder::toCommandID(j, command.type()));
    }
  }
}

void insertSetters(CommandRecordTable* table, Listener<None>* ln) {
  insert(table, setters());

  for (int i = 0; i < setters().command_size(); ++i) {
    const Command& cmd = setters().command(i);
    int id = cmd.type();
    CommandRecord* cr = find(table, id);

    if (cr->setter_)
      LOG(ERROR) << "Duplicate setter " << commandName(id);

    using slow::GuiSettings;
    using audio::stretch::Stretch;

    const data::Address& a = cmd.address();
    if (id == Command::TOGGLE_GRID_DISPLAY) {
      cr->setter_.reset(new CommandDataSetter<GuiSettings>(ln, cmd, a, true));

    } else if (id == Command::TOGGLE_STRETCH_ENABLE) {
      cr->setter_.reset(new CommandDataSetter<Stretch>(ln, cmd, a, false));

    } else {
      LOG(ERROR) << "Didn't understand " << commandName(id);
      continue;
    }

    if (cr->callback_)
      LOG(ERROR) << "Duplicate callback " << commandName(id);

    cr->callback_.reset(thread::methodCallback(cr->setter_.get(),
                                               &CommandItemSetter::execute));
  }
}

void mergeKeyPresses(CommandRecordTable* table, const Access& access) {
  Commands kp = keyPresses(access);
  for (int i = 0; i < kp.command_size(); ++i)
    merge(table, kp.command(i));
}

void mergeDescriptions(CommandRecordTable* table, const Access& access) {
  const Commands& desc = descriptions(access);
  for (int i = 0; i < desc.command_size(); ++i)
    mergeDescription(table, desc.command(i));
}

void removeEmpties(CommandRecordTable* table) {
  std::vector<CommandID> empties;
  CommandRecordTable::iterator i;
  for (i = table->begin(); i != table->end(); ++i) {
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
      LOG(ERROR) << "Removing " << commandName(i->first)
                 << " because " << error;
      CHECK(false);
    }
  }

  for (int i = 0; i < empties.size(); ++i)
    table->erase(empties[i]);
}

}  // namespace command
}  // namespace rec
