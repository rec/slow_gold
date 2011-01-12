#ifndef __REC_UTIL_DEFAULTER__
#define __REC_UTIL_DEFAULTER__

#include "rec/base/base.h"

namespace rec {
namespace util {

bool fillFromDefault(const string& dflt, Message* creator);

template <typename Proto>
class Defaulter {
 public:
  explicit Defaulter(const string& dflt) { fillFromDefault(dflt, &proto_); }
  const Proto& get(const Proto* p = NULL) { return p ? *p : proto_; }

 private:
  Proto proto_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DEFAULTER__
