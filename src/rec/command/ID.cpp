#include "rec/command/ID.h"

#include "rec/util/Math.h"

namespace rec {
namespace command {

namespace {

const int SIZE = Command::BANK_SIZE;

int32 toID(int32 position, int32 type) {
  return (type * SIZE) + (position - ID::FIRST);
}

}  // namespace

ID::ID(int command, int index) : command_(toID(index, command)) {}

ID::ID(const Command& command) : command_(command.type()) {
  if (command.has_start_index())
    command_ = toID(command.start_index(), command_);
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