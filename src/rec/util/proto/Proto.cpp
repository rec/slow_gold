#include <google/protobuf/descriptor.h>

#include "rec/util/proto/Proto.h"
#include "rec/program/Program.h"

namespace rec {
namespace util {

string getTypeName(const Message& m) {
  return program::getProgram()->getTypeName(m);
}

}  // namespace util
}  // namespace rec
