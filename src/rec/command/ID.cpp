#include "rec/command/ID.h"

#include "rec/command/CommandIDEncoder.h"
#include "rec/util/Math.h"

namespace rec {
namespace command {

// namespace {

const int SIZE = Command::BANK_SIZE;

CommandIDEncoder fromCommandID(CommandID id) {
  static const int SIZE = Command::BANK_SIZE;
  return CommandIDEncoder((id < SIZE) ? CommandIDEncoder::CURRENT :
                          mod(id, SIZE) + CommandIDEncoder::FIRST);
}

int toCommandID(const Command& cmd) {
  return cmd.has_index() ? toCommandID(cmd.index(), cmd.type()) : cmd.type();
}

void fillCommandFromId(CommandID id, Command* command) {
  if (id >= Command::BANK_SIZE) {
    command->set_index(fromCommandID(id).position_);
    id /= Command::BANK_SIZE;
  }
  command->set_type(static_cast<Command::Type>(id));
}

CommandID toCommandID(int32 position, int32 type) {
  return CommandIDEncoder(position).toCommandID(type);
}

// }  // namespace

ID::ID(int command, int index)
    : command_(toCommandID(index, command)) {
}

ID::ID(const Command& command) : command_(command.type()) {
  if (command.has_start_index())
    command_ = toCommandID(command.start_index(), command_);
}

const ID::Type ID::type() const {
  int body = command_ / Command::BANK_SIZE;
  int remains = command_ % Command::BANK_SIZE;

  return static_cast<Command::Type>(body ? body : remains);
}

const int ID::index() const {
  return (command_ < SIZE) ? CURRENT : mod(command_, SIZE) + FIRST;
}

bool ID::hasIndex() const {
  return command_ > Command::BANK_SIZE;
}

string ID::name() const {
  Command::Type t = type();
  string res;

  int body = command_ / Command::BANK_SIZE;
  int remains = command_ % Command::BANK_SIZE;

  int position = body ? remains : 0;

  string name;
  if (t <= Command::LAST_TYPE ||
      (t >= Command::JUCE_START && t <= Command::JUCE_END)) {
    name = Command::Type_Name(t);
  } else {
    name = "Bad id " + str(String(t));
    DCHECK(false) << name;
  }

  if (body) {
    name += ": ";

    switch (position + FIRST) {
     case FIRST: name += "FIRST"; break;
     case PREVIOUS: name += "PREVIOUS"; break;
     case CURRENT: name += "CURRENT"; break;
     case NEXT: name += "NEXT"; break;
     case LAST: name += "LAST"; break;
     default: name += str(String(position + FIRST)); break;
    }
  }
  return name;
}

}  // namespace command
}  // namespace rec
