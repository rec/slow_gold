#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "rec/util/Proto.h"

namespace rec {
namespace util {

const string& getTypeName(const Message& m) {
  return m.GetDescriptor()->name();
}

}  // namespace util
}  // namespace rec
