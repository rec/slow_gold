#ifndef __REC_UTIL_UPDATEREQUESTER__
#define __REC_UTIL_UPDATEREQUESTER__

#include "rec/base/base.h"

namespace rec {
namespace util {

class UpdateRequester {
 public:
  UpdateRequester();
  virtual ~UpdateRequester() {}

  virtual void requestUpdates() = 0;
  static void requestAllUpdates();
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UPDATEREQUESTER__
