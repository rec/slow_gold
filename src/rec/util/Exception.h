#ifndef __REC_UTIL_EXCEPTION__
#define __REC_UTIL_EXCEPTION__

#include <exception>

#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace util {
namespace cd {

class Exception : public std::exception {
 public:
  explicit Exception(const string& m) : message_(m) {}
  virtual ~Exception() throw() {}
  virtual const char* what() const throw() { return message_.c_str(); }

 private:
  const string message_;
};

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_EXCEPTION__
