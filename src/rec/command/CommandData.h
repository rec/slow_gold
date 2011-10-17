#ifndef __REC_COMMAND_COMMANDDATA__
#define __REC_COMMAND_COMMANDDATA__

#include "rec/Command/Command.h"

namespace rec {
namespace command {

class Access;

const Commands& commands();
const Commands& descriptions(const Access&);
const Commands& keyPresses(const Access&);

enum MergeType { NEW, MERGE };

void merge(CommandTable*, const Commands&, MergeType mergeType = MERGE);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATA__
