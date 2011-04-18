#ifndef __REC_SLOW_PERSISTENTDATA__
#define __REC_SLOW_PERSISTENTDATA__

#include "rec/data/persist/Persist.h"

namespace rec {
namespace slow {

struct PersistentData {
  persist::Data<LoopPointList>* loopPointList_;
  persist::Data<StretchLoop>* stretchLoop_;
  persist::Data<ZoomProto>* zoomProto_;

  PersistentData() : loopPointList_(NULL),
                     stretchLoop_(NULL),
                     zoomProto_(NULL) {
  }

  void setFile(const VirtualFile* file) {
    if (file && !empty(*file)) {
      loopPointList_ = persist::data<LoopPointList>(file);
      stretchLoop_ = persist::data<StretchLoop>(file);
      zoomProto_ = persist::data<ZoomProto>(file);
    } else {
      *this = PersistentData();
    }
  }

}

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PERSISTENTDATA__
