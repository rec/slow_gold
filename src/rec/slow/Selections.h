#ifndef __REC_SLOW_SELECTIONS__
#define __REC_SLOW_SELECTIONS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Instance;

void addLoopPoint(Instance*);

#ifdef EXTEND_CONTRACT
void extendEnd(Instance*);
void retractEnd(Instance*);
void extendBegin(Instance*);
void retractBegin(Instance*);
#endif

void jumpToNextLoopPointInSelection(Instance*);
void jumpToPreviousLoopPointInSelection(Instance*);
void jumpToStartOfSelection(Instance*);
void jumpToEndOfSelection(Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SELECTIONS__
