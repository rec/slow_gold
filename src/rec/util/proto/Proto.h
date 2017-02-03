#pragma once

#include <google/protobuf/message.h>

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Proto>
string getTypeName() {
    return Proto::default_instance().GetTypeName();
}

inline Message* clone(const Message& m) {
  std::unique_ptr<Message> p(m.New());
  p->CopyFrom(m);
  return p.release();
}

inline Message* clone(const Message* m) {
  return m ? clone(*m) : nullptr;
}

}  // namespace util
}  // namespace rec
