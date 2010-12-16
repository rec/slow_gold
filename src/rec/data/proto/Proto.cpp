#include <glog/logging.h>

#include "rec/data/proto/Field.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation, Message* msg) {
  return Field::apply(operation, msg);
}

Value getValue(const Address& address, const Message& msg) {
  return Field::apply(address, msg);
}

}  // namespace proto
}  // namespace rec
