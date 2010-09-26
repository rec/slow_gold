#include <glog/logging.h>

#include "rec/base/scoped_ptr.h"
#include "google/protobuf/descriptor.h"
#include "rec/proto/Proto.h"
#include "rec/proto/Field.h"
#include "rec/proto/TypedTyper.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation,
                          google::protobuf::Message* msg) {
  return Field::apply(operation, msg);
}

}  // namespace proto
}  // namespace rec
