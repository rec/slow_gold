#include "rec/audio/stretch/Stretch.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/data/CommandData.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace command {

namespace {

using slow::Position;

enum MergeType {INSERT, MERGE};

void addTo(MergeType type, CommandTable* commands, const Command& cmd,
           CommandID id = 0) {
  if (!id)
    id = Position::toCommandID(cmd);

  CommandTable::iterator j = commands->find(id);
  if (j == commands->end()) {
    if (type == INSERT)
      commands->insert(j, std::make_pair(id, new Command(cmd)));
    else
    LOG(ERROR) << "No existing command " << Position::commandIDName(id);
  } else {
    if (type == MERGE)
      j->second->MergeFrom(cmd);
    else
      LOG(ERROR) << "Can't replace " << Position::commandIDName(id);
  }
}

void merge(CommandTable* commands, const Command& cmd, CommandID id = 0) {
  addTo(MERGE, commands, cmd, id);
}

void insert(CommandTable* commands, const Command& cmd, CommandID id = 0) {
  addTo(INSERT, commands, cmd, id);
}

void insertSingle(CommandTable* cmds) {
  for (int i = 0; i < commands().command_size(); ++i)
    insert(cmds, commands().command(i));
}

void insertRepeated(CommandTable* commands) {
  for (int i = 0; i < repeated().command_size(); ++i) {
    const Command& command = repeated().command(i);
    Command c = command;

    // Insert each specific subcommand.
    for (int j = Position::FIRST; j < command.index(); ++j) {
      c.set_index(j);
      insert(commands, c, Position::toCommandID(j, command.type()));
    }
  }
}

void insertSetters(CommandContext* context, Listener<None>* listener) {
  SetterTable* table = &context->setters_;
  for (int i = 0; i < setters().command_size(); ++i) {
    Command cmd = setters().command(i);
    insert(&context->commands_, cmd);
    int id = cmd.type();
    ptr<CommandItemSetter> setter;
    const data::Address& addr = cmd.address();

    using slow::GuiSettings;
    using audio::stretch::Stretch;

    if (id == Command::TOGGLE_GRID_DISPLAY)
      setter.reset(new CommandDataSetter<GuiSettings>(listener, cmd, addr, true));

    else if (id == Command::TOGGLE_STRETCH_ENABLE)
      setter.reset(new CommandDataSetter<Stretch>(listener, cmd, addr, false));

    else
      LOG(ERROR) << "Didn't understand " << Position::commandIDName(id);

    if (setter) {
      SetterTable::iterator i = table->find(id);
      if (i != table->end()) {
        LOG(ERROR) << "Found a duplicate setter " << Position::commandIDName(id);
        delete i->second;
      }
      context->callbacks_[id] = thread::methodCallback(
          setter.get(), &CommandItemSetter::execute);
      table->insert(i, std::make_pair(id, setter.transfer()));
      LOG(ERROR) << "Inserted setter " << Position::commandIDName(id);
    }
  }
}

void mergeKeyPresses(CommandTable* commands, const Access& access) {
  Commands kp = keyPresses(access);
  for (int i = 0; i < kp.command_size(); ++i)
    merge(commands, kp.command(i));
}

void mergeDescription(CommandTable* commands, const Command& command) {
  CommandTable::iterator it = commands->find(command.type());
  if (it != commands->end()) {
    it->second->MergeFrom(command);
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
  for (int i = 0; i <= Position::LAST - Position::FIRST; ++i, ++c) {
    it = commands->find(c);
    if (it == commands->end()) {
      LOG(ERROR) << "Couldn't find position " << i
                 << " CommandID " << c
                 << " cmd: " << command.ShortDebugString();
      return;
    }
    Description* desc = it->second->mutable_desc();
    desc->add_menu(str(String::formatted(menu, CAP[i], "")));
    desc->set_full(str(String::formatted(full, LOWER[i], "")));
  }

  for (int i = 0; ; ++i, ++c) {
    it = commands->find(c);
    if (it == commands->end())
      break;

    String n = " " + String(i + 1);
    const char* s = n.toUTF8();
    Description* desc = it->second->mutable_desc();
    desc->add_menu(str(String::formatted(menu, "", s)));
    desc->set_full(str(String::formatted(full, "", s)));
  }
}

void mergeDescriptions(CommandTable* commands, const Access& access) {
  const Commands& desc = descriptions(access);
  for (int i = 0; i < desc.command_size(); ++i)
    mergeDescription(commands, desc.command(i));
}

void removeEmpties(CommandTable* commands) {
  std::vector<CommandID> empties;
  for (CommandTable::const_iterator i = commands->begin();
       i != commands->end(); ++i) {
    const Description& desc = i->second->desc();
    if (!(desc.menu().size() && desc.full().size())) {
      empties.push_back(i->first);
      LOG(ERROR) << "Removing empty command "
                 << Position::commandIDName(i->first);
    }
  }

  for (int i = 0; i < empties.size(); ++i)
    commands->erase(empties[i]);
}

}  // namespace

const Commands fromCommandTable(const CommandTable& table) {
  Commands commands;
  for (CommandTable::const_iterator i = table.begin(); i != table.end(); ++i)
    commands.add_command()->CopyFrom(*(i->second));
  return commands;
}

const CommandTable toCommandTable(const Commands& commands) {
  CommandTable table;
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& c = commands.command(i);
    table[slow::Position::toCommandID(c)] = new Command(c);
  }
  return table;
}

CommandContext::CommandContext(Listener<None>* listener) {
  Access access = data::get<Access>();

  insertSingle(&commands_);
  insertRepeated(&commands_);
  insertSetters(this, listener);
  mergeKeyPresses(&commands_, access);
  mergeDescriptions(&commands_, access);
  removeEmpties(&commands_);
}

CommandContext::~CommandContext() {
  stl::deleteMapPointers(&commands_);
  stl::deleteMapPointers(&setters_);
  stl::deleteMapPointers(&callbacks_);  // TODO: this causes a crash on exit.
}

}  // namespace command
}  // namespace rec
