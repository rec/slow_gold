#include <google/protobuf/text_format.h>

#include "rec/util/Defaulter.h"

namespace rec {
namespace util {

bool fillFromDefault(const string& dflt, Message* msg) {
  return google::protobuf::TextFormat::ParseFromString(dflt, msg);
}

}  // namespace util
}  // namespace rec
