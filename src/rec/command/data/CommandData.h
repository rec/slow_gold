#ifndef __REC_COMMAND_COMMANDDATA__
#define __REC_COMMAND_COMMANDDATA__

#include "rec/Command/Command.h"

namespace rec {
namespace command {

class Access;

const Commands& commands();
const Commands& repeated();
const Commands& descriptions(const Access&);
const Commands& keyPresses(const Access&);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATA__
