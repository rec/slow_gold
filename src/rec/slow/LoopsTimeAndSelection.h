#ifndef __REC_SLOW_LOOPSTIMEANDSELECTION__
#define __REC_SLOW_LOOPSTIMEANDSELECTION__

#include "rec/slow/HasInstance.h"
#include "rec/slow/Model.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

class LoopsTimeAndSelection : public HasInstance {
 public:
  LoopsTimeAndSelection(Instance* i);

  void toggleWholeSongLoop();
  void jumpToNextLoopPoint();
  void jumpToPreviousLoopPoint();
  void jumpToStart();
  void jumpToNextLoopPointInSelection();
  void jumpToPreviousLoopPointInSelection();
  void jumpToStartOfSelection();

 private:
  void setData();
  int getContainingSegment() const;

  LoopPointList loops_;
  SamplePosition time_;
  int segment_;
  SampleSelection selection_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPSTIMEANDSELECTION__
