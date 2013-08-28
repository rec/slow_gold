#ifndef __REC_UTIL_DEFAULTER__
#define __REC_UTIL_DEFAULTER__

#include "rec/base/base.h"

namespace rec {
namespace util {

bool fillFromDefault(const string&, Message*);

template <typename Proto>
class Def {
 public:
  explicit Def(const string& dflt) { fillFromDefault(dflt, &proto_); }
  const Proto& get() const { return proto_; }
  const Proto& operator*() const { return get(); }

 private:
  Proto proto_;
};


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DEFAULTER__
