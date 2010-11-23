#ifndef __REC_UTIL_DEFAULTER__
#define __REC_UTIL_DEFAULTER__

#include "rec/base/base.h"

namespace rec {
namespace util {

bool fillFromDefault(const string& dflt, Message* creator);

template <typename Proto>
class Defaulter {
 public:
  Defaulter(const string& dflt) { fillFromDefault(dflt, &proto_); }
  const Proto& get(const Proto* p) { return p ? *p : proto_; }

 private:
  const Proto proto_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DEFAULTER__
