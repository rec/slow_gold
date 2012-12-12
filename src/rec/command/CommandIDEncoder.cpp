#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace command {

CommandID CommandIDEncoder::toCommandID(int32 type) {
  return (type * Command::BANK_SIZE) + (position_ - FIRST);
}


}  // namespace command
}  // namespace rec

