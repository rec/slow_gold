#ifndef __REC_SLOW_LOOPCOMMANDS__
#define __REC_SLOW_LOOPCOMMANDS__

#include "rec/audio/Audio.h"
#include "rec/command/Command.h"

namespace rec {
namespace slow {

class Instance;

bool executeLoopCommand(Instance*, command::Command::Type);
void toggleSelectionSegment(const VirtualFile&, RealTime);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPCOMMANDS__
