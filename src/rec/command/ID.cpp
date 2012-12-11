#include "rec/command/ID.h"

#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

ID::ID(int command, int index)
    : command_(CommandIDEncoder::toCommandID(index, command)) {
}

const ID::Type ID::type() const {
  return CommandIDEncoder::getType(command_);
}

const int ID::index() const {
  return CommandIDEncoder::fromCommandID(command_).getPosition();
}

bool ID::hasIndex() const {
  return command_ > Command::BANK_SIZE;
}

string ID::name() const {
  return CommandIDEncoder::commandIDName(command_);
}

}  // namespace command
}  // namespace rec
