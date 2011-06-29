#ifndef __REC_SLOW_SELECTIONS__
#define __REC_SLOW_SELECTIONS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Instance;

void addLoopPoint(Instance*);
void selectAll(Instance*);
void selectNone(Instance*);
void selectInvert(Instance*);

void extendEnd(Instance*);
void retractEnd(Instance*);
void extendBegin(Instance*);
void retractBegin(Instance*);

void selectNextOnly(Instance*);
void selectPreviousOnly(Instance*);

void selectItem(Instance*, int);
void selectItemOnly(Instance*, int);
void unselectItem(Instance*, int);
void toggleItem(Instance*, int);

void toggleWholeSongLoop(Instance*);
void jumpToNextLoopPoint(Instance*);
void jumpToPreviousLoopPoint(Instance*);
void jumpToStart(Instance*);
void jumpToNextLoopPointInSelection(Instance*);
void jumpToPreviousLoopPointInSelection(Instance*);
void jumpToStartOfSelection(Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SELECTIONS__
