#ifndef __REC_UTIL_PROTO__
#define __REC_UTIL_PROTO__

#include <google/protobuf/message.h>

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Proto>
string getTypeName() {
  return Proto::default_instance().GetTypeName();
}

// A little slower because it uses reflection.
const string& getTypeName(const Message&);

inline Message* clone(const Message& m) {
  ptr<Message> p(m.New());
  p->CopyFrom(m);
  return p.transfer();
}

inline Message* clone(const Message* m) {
  return m ? clone(*m) : NULL;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PROTO__