#include "rec/command/CommandName.h"

#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

CommandName::CommandName(int command, int index)
    : command_(CommandIDEncoder::toCommandID(index, command)) {
}

const CommandName::Type CommandName::type() const {
  return CommandIDEncoder::getType(command_);
}

const int CommandName::index() const {
  return CommandIDEncoder::fromCommandID(command_).getPosition();
}

bool CommandName::hasIndex() const {
  return command_ > Command::BANK_SIZE;
}

string CommandName::name() const {
  return CommandIDEncoder::commandIDName(command_);
}

}  // namespace command
}  // namespace rec
