#include <google/protobuf/text_format.h>

#include "rec/util/Defaulter.h"
#include "rec/util/Copy.h"

namespace rec {
namespace util {

bool fillFromDefault(const string& dflt, Message* msg) {
  return copy::copy(dflt, msg, copy::READABLE);
}

}  // namespace util
}  // namespace rec
