#include "rec/slow/PersistentData.h"

namespace rec {
namespace slow {

PersistentData::PersistentData()
  : loopPointList_(NULL), stretchLoop_(NULL), zoomProto_(NULL) {
}

void PersistentData::setFile(const VirtualFile* file) {
  if (file && !empty(*file)) {
    loopPointList_ = persist::data<gui::audio::LoopPointList>(file);
    stretchLoop_ = persist::data<audio::stretch::StretchLoop>(file);
    zoomProto_ = persist::data<widget::waveform::ZoomProto>(file);
  } else {
    *this = PersistentData();
  }
}

}  // namespace slow
}  // namespace rec
