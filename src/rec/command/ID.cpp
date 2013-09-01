#include "rec/command/ID.h"

#include "rec/command/Command.pb.h"
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

const int ID::index() const {
  return (command_ < SIZE) ? CURRENT : mod(command_, SIZE) + FIRST;
}

bool ID::hasIndex() const {
  return command_ > Command::BANK_SIZE;
}

}  // namespace command
}  // namespace rec
