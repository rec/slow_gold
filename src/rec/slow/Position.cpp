#include "rec/slow/Position.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

static const int SIZE = Command::BANK_SIZE;

int Position::toIndex(int32 segment, int32 size) {
  int pos = (position_ == FIRST) ? 0 :
    (position_ == PREVIOUS) ? segment - 1 :
    (position_ == CURRENT) ? segment :
    (position_ == NEXT) ? segment + 1 :
    (position_ == LAST) ? size - 1 :
    position_;
  return mod(pos, size);
}

CommandID Position::toCommandID(int32 type) {
  return (type * Command::BANK_SIZE) + (position_ - FIRST);
}

// static
Position Position::fromCommandID(CommandID id) {
  static const int SIZE = Command::BANK_SIZE;
  return Position((id < SIZE) ? CURRENT : mod(id, SIZE) + FIRST);
}

// static
string Position::commandIDName(CommandID id) {
  string res;

  int body = id / Command::BANK_SIZE;
  int remains = id % Command::BANK_SIZE;

  Command::Type type = static_cast<Command::Type>(body ? body : remains);
  int position = body ? remains : 0;

  string name;
  if (type <= Command::LAST_TYPE ||
      (type >= Command::JUCE_START && type <= Command::JUCE_END)) {
    name = Command::Type_Name(type);
  } else {
    name = "Bad id " + str(String(type));
    DCHECK(false);
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

int Position::toCommandID(const Command& cmd) {
  return cmd.has_index() ? toCommandID(cmd.index(), cmd.type()) : cmd.type();
}

void Position::fillCommandFromId(CommandID id, Command* command) {
  if (id >= Command::BANK_SIZE) {
    command->set_index(fromCommandID(id));
    id /= Command::BANK_SIZE;
  }
  command->set_type(static_cast<Command::Type>(id));
}

}  // namespace slow
}  // namespace rec
