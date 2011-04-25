#ifndef __REC_UTIL_REFERENCE__
#define __REC_UTIL_REFERENCE__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
class Reference {
 public:
  Reference() : reference_(NULL) {}
  virtual ~Reference() {}

  virtual Type* getData() const { return reference_; }
  virtual void setData(Type* r) { reference_ = r; }

 private:
  Type* reference_;

  DISALLOW_COPY_AND_ASSIGN(Reference);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_REFERENCE__
