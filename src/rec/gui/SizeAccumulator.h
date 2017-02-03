#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class SizeAccumulator {
 public:
  SizeAccumulator() { clear(); }

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

  void clear() {
    totalAbsolute_ = 0;
    totalRatio_ = 0.0;
  }

 private:
  int totalAbsolute_;
  double totalRatio_;
};


}  // namespace gui
}  // namespace rec

