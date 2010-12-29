#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "rec/data/proto/GetProtoName.h"

namespace rec {
namespace data {
namespace proto {

const string& getName(const Message& m) { return m.GetDescriptor()->name(); }

}  // namespace proto
}  // namespace data
}  // namespace rec
