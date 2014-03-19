#include <google/protobuf/descriptor.h>

#include "rec/util/proto/Proto.h"
#include "rec/program/Program.h"

namespace rec {
namespace util {

string getTypeName(const Message& message) {
  auto s = message.GetTypeName();

  if (auto prog = program::getProgram())
    s = prog->mapTypeName(s);

  return s;
}

}  // namespace util
}  // namespace rec
