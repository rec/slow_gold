#include "rec/audio/stretch/Stretch.h"
#include "rec/command/CommandDatabase.h"
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

void addTo(MergeType type, CommandContext* context, const Command& cmd,
           CommandID id = 0) {
  if (!id)
    id = Position::toCommandID(cmd);

  CommandTable::iterator j = context->commands_.find(id);
  if (j == context->commands_.end()) {
    if (type == INSERT)
      context->commands_.insert(j, std::make_pair(id, new Command(cmd)));
    else
    LOG(ERROR) << "No existing command " << Position::commandIDName(id);
  } else {
    if (type == MERGE)
      j->second->MergeFrom(cmd);
    else
      LOG(ERROR) << "Can't replace " << Position::commandIDName(id);
  }
}

void merge(CommandContext* context, const Command& cmd, CommandID id = 0) {
  addTo(MERGE, context, cmd, id);
}

void insert(CommandContext* context, const Command& cmd, CommandID id = 0) {
  addTo(INSERT, context, cmd, id);
}

}  // namespace

CommandDatabase::CommandDatabase() {
  recalculate();
}

CommandDatabase::~CommandDatabase() {
  clear();
}

void CommandDatabase::clear() {
  stl::deleteMapPointers(&context_.commands_);
  stl::deleteMapPointers(&context_.setters_);

  context_.commands_.clear();
  context_.setters_.clear();
}

const Command CommandDatabase::command(CommandID t) const {
  Lock l(lock_);

  CommandTable::const_iterator i = context_.commands_.find(t);
  return (i == context_.commands_.end()) ?
    Command::default_instance() : *(i->second);
}

namespace {

void insertSingle(CommandContext* context) {
  for (int i = 0; i < commands().command_size(); ++i)
    insert(context, commands().command(i));
}

void insertRepeated(CommandContext* context) {
  for (int i = 0; i < repeated().command_size(); ++i) {
    const Command& command = repeated().command(i);
    Command c = command;

    // Insert each specific subcommand.
    for (int j = Position::FIRST; j < command.index(); ++j) {
      c.set_index(j);
      insert(context, c, Position::toCommandID(j, command.type()));
    }
  }
}

void insertSetters(CommandContext* context) {
  SetterTable* table = &context->setters_;
  for (int i = 0; i < setters().command_size(); ++i) {
    Command cmd = setters().command(i);
    insert(context, cmd);
    int id = cmd.type();
    ptr<CommandItemSetter> setter;
    const data::Address& addr = cmd.address();

    using slow::GuiSettings;
    using audio::stretch::Stretch;

    if (id == Command::TOGGLE_GRID_DISPLAY)
      setter.reset(new CommandDataSetter<GuiSettings>(cmd, addr, true));

    else if (id == Command::TOGGLE_STRETCH_ENABLE)
      setter.reset(new CommandDataSetter<Stretch>(cmd, addr, false));

    else
      LOG(ERROR) << "Didn't understand " << Position::commandIDName(id);

    if (setter) {
      SetterTable::iterator i = table->find(id);
      if (i != table->end()) {
        LOG(ERROR) << "Found a duplicate setter " << Position::commandIDName(id);
        delete i->second;
      }
      context->callbacks_[id] = setter.get();
      table->insert(i, std::make_pair(id, setter.transfer()));
    }
  }
}

void mergeKeyPresses(CommandContext* context, const Access& access) {
  Commands kp = keyPresses(access);
  for (int i = 0; i < kp.command_size(); ++i)
    merge(context, kp.command(i));
}

void mergeDescription(CommandContext* context, const Command& command) {
  CommandTable::iterator it = context->commands_.find(command.type());
  if (it != context->commands_.end()) {
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
    it = context->commands_.find(c);
    if (it == context->commands_.end()) {
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
    it = context->commands_.find(c);
    if (it == context->commands_.end())
      break;

    String n = " " + String(i + 1);
    const char* s = n.toUTF8();
    Description* desc = it->second->mutable_desc();
    desc->add_menu(str(String::formatted(menu, "", s)));
    desc->set_full(str(String::formatted(full, "", s)));
  }
}

void mergeDescriptions(CommandContext* context, const Access& access) {
  const Commands& desc = descriptions(access);
  for (int i = 0; i < desc.command_size(); ++i)
    mergeDescription(context, desc.command(i));
}

void removeEmpties(CommandContext* context) {
  std::vector<CommandID> empties;
  for (CommandTable::const_iterator i = context->commands_.begin();
       i != context->commands_.end(); ++i) {
    const Description& desc = i->second->desc();
    if (!(desc.menu().size() && desc.full().size())) {
      empties.push_back(i->first);
      LOG(ERROR) << "Removing empty command "
                 << Position::commandIDName(i->first);
    }
  }

  for (int i = 0; i < empties.size(); ++i)
    context->commands_.erase(empties[i]);
}

}  // namespace

void CommandDatabase::recalculate() {
  Lock l(lock_);
  Access access = data::get<Access>();
  clear();

  insertSingle(&context_);
  insertRepeated(&context_);
  insertSetters(&context_);
  mergeKeyPresses(&context_, access);
  mergeDescriptions(&context_, access);
  removeEmpties(&context_);
}

}  // namespace command
}  // namespace rec
