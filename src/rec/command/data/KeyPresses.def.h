#ifndef __REC_COMMAND_DATA_KEYPRESSES__
#define __REC_COMMAND_DATA_KEYPRESSES__

// Created by the command line:
// new --include=command/Command --proto=Commands KeyPresses.def

#include "rec/command/Command.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace command {
namespace data {

extern Def<Commands> keyPresses;

}  // namespace data
}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_DATA_KEYPRESSES__
