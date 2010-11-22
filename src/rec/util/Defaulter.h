#ifndef __REC_UTIL_DEFAULTER__
#define __REC_UTIL_DEFAULTER__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Proto, typename Initializer>
const Proto* getDefault(Initializer init) {
  Proto* pr = new Proto();
  init(pr);
  return pr;
}

template <typename Proto, typename Initializer>
const Proto* getOrDefault(const Proto* pr, Initializer init) {
  static const Proto* dflt = getDefault<Proto, Initializer>(init);
  return pr ? pr : dflt;
}

}  // namespace util
}  // namespace rec

#define GET_OR_DEFAULT(P, F, I) ((P.has_ ## F()) ? &P.F() : getOrDefault(&P, I))

#endif  // __REC_UTIL_DEFAULTER__
