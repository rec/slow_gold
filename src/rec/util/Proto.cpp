#include <google/protobuf/descriptor.h>

#include "rec/util/Proto.h"

namespace rec {
namespace util {

const string& getTypeName(const Message& m) {
  return m.GetDescriptor()->full_name();
}

}  // namespace util
}  // namespace rec
