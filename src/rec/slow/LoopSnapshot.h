#pragma once

#include <map>

#include "rec/base/base.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {

namespace util { class LoopPointList; }

namespace slow {

class Instance;

struct LoopSnapshot {
  LoopSnapshot() {}
  LoopSnapshot(Instance*);

  Instance* instance_;
  widget::waveform::Viewport viewport_;
  LoopPointList* loops_;

  typedef bool (*Function)(LoopSnapshot*);
  typedef std::map<int32, LoopSnapshot::Function> Map;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(LoopSnapshot);
};

}  // namespace slow
}  // namespace rec

