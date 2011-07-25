#include "rec/slow/PersistentData.h"

namespace rec {
namespace slow {

PersistentData::PersistentData()
  : loopPointList_(NULL), stretch_(NULL), zoomProto_(NULL) {
}

void PersistentData::setFile(const VirtualFile* file) {
  if (file && !empty(*file)) {
    loopPointList_ = persist::setter<LoopPointList>(*file);
    stretch_ = persist::setter<audio::stretch::Stretch>(*file);
    zoomProto_ = persist::setter<widget::waveform::ZoomProto>(*file);
  } else {
    *this = PersistentData();
  }
}

}  // namespace slow
}  // namespace rec
