#ifndef __REC_UTIL_EXCEPTION__
#define __REC_UTIL_EXCEPTION__

#include <exception>

#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace util {
namespace cd {

class Exception : public exception {
 public:
  explicit Exception(const String& m) : message_(m) {}
  virtual const char* what() const { return m.toCString(); }

 private:
  const String message_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Exception);
};

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_EXCEPTION__
