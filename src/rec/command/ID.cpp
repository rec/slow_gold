#include "rec/command/ID.h"

#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

ID::ID(int command, int index)
    : command_(CommandIDEncoder::toCommandID(index, command)) {
}

ID::ID(const Command& command) : command_(command.type()) {
  if (command.has_start_index())
    command_ = CommandIDEncoder::toCommandID(command.start_index(), command_);
}

const ID::Type ID::type() const {
  return CommandIDEncoder::getType(command_);
}

const int ID::index() const {
  return CommandIDEncoder::fromCommandID(command_).position_;
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
