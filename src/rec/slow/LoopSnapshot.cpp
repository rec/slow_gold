#include "rec/slow/LoopSnapshot.h"

#include "rec/audio/source/Player.h"
#include "rec/data/DataOps.h"
#include "rec/slow/Instance.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(data::getProto<LoopPointList>(i->file())){
}

}  // namespace slow
}  // namespace rec

