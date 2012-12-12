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

}  // namespace command
}  // namespace rec

