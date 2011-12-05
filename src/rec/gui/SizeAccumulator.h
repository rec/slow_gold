#ifndef __REC_GUI_SIZEACCUMULATOR__
#define __REC_GUI_SIZEACCUMULATOR__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class SizeAccumulator {
 public:
  SizeAccumulator() : totalAbsolute_(0), totalRatio_(0.0) {}

  void accumulate(double size) {
    if (size >= 0.0) {
      totalAbsolute_ += static_cast<int>(size);
    } else {
      totalRatio_ -= size;
      // DCHECK_LT(totalRatio_, 1.0);
    }
  }

  int size() const {
    if (totalRatio_ >= 1) {
      // LOG(DFATAL) << "Impossible size!";
      return totalAbsolute_;
    }

    return static_cast<int>(totalAbsolute_ / (1.0 - totalRatio_));
  }

 private:
  int totalAbsolute_;
  double totalRatio_;
};


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SIZEACCUMULATOR__
