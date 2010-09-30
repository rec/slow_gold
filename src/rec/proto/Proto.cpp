#include <glog/logging.h>

#include "rec/proto/Field.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation, Message* msg) {
  return Field::apply(operation, msg);
}

}  // namespace proto
}  // namespace rec
