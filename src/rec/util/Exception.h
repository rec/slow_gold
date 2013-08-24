#ifndef __REC_UTIL_EXCEPTION__
#define __REC_UTIL_EXCEPTION__

#include <exception>

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

class Exception : public std::exception {
 public:
  explicit Exception(const string& m) : message_(m) {}
  explicit Exception(const String& m) : message_(m.toStdString()) {}
  virtual ~Exception() throw() {}
  virtual const char* what() const throw() { return message_.c_str(); }

 private:
  const string message_;
};

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_EXCEPTION__
