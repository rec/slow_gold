#include "rec/command/CommandIDEncoder.h"
#include "rec/util/Math.h"

namespace rec {
namespace command {

static const int SIZE = Command::BANK_SIZE;

CommandID CommandIDEncoder::toCommandID(int32 type) {
  return (type * Command::BANK_SIZE) + (position_ - FIRST);
}

// static
CommandIDEncoder CommandIDEncoder::fromCommandID(CommandID id) {
  static const int SIZE = Command::BANK_SIZE;
  return CommandIDEncoder((id < SIZE) ? CURRENT : mod(id, SIZE) + FIRST);
}

// static
string CommandIDEncoder::commandIDName(CommandID id) {
  Command::Type type = getType(id);
  string res;

  int body = id / Command::BANK_SIZE;
  int remains = id % Command::BANK_SIZE;

  int position = body ? remains : 0;

  string name;
  if (type <= Command::LAST_TYPE ||
      (type >= Command::JUCE_START && type <= Command::JUCE_END)) {
    name = Command::Type_Name(type);
  } else {
    name = "Bad id " + str(String(type));
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
  return name; //  + " " + str(String(id));
}

int CommandIDEncoder::toCommandID(const Command& cmd) {
  return cmd.has_index() ? toCommandID(cmd.index(), cmd.type()) : cmd.type();
}

void CommandIDEncoder::fillCommandFromId(CommandID id, Command* command) {
  if (id >= Command::BANK_SIZE) {
    command->set_index(fromCommandID(id).position_);
    id /= Command::BANK_SIZE;
  }
  command->set_type(static_cast<Command::Type>(id));
}

Command::Type CommandIDEncoder::getType(CommandID id) {
  int body = id / Command::BANK_SIZE;
  int remains = id % Command::BANK_SIZE;

  return static_cast<Command::Type>(body ? body : remains);
}

}  // namespace command
}  // namespace rec

