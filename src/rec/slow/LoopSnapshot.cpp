#include "rec/slow/LoopSnapshot.h"

#include "rec/data/DataOps.h"
#include "rec/slow/Instance.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace slow {

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    viewport_(data::getProto<widget::waveform::Viewport>(i->file())),
    loops_(viewport_.mutable_loop_points()) {
}

}  // namespace slow
}  // namespace rec

