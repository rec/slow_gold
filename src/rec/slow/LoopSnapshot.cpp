#include "rec/slow/LoopSnapshot.h"

#include "rec/util/LoopPoint.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/BufferFiller.h"

namespace rec {
namespace slow {

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(data::get<LoopPointList>(&i->file())){
}

}  // namespace slow
}  // namespace rec

