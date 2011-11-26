#ifndef __REC_COMMAND_DATA_SLOWCOMMANDDATA__
#define __REC_COMMAND_DATA_SLOWCOMMANDDATA__

#include "rec/base/base.h"

namespace rec {

namespace command { class CommandData; }

namespace slow {

class Instance;

command::CommandData* createSlowCommandData(Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_DATA_SLOWCOMMANDDATA__
