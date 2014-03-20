#include <google/protobuf/descriptor.h>

#include "rec/util/proto/Proto.h"
#include "rec/program/Program.h"

namespace rec {
namespace util {

#if 0
string getTypeName(const Message& message) {
  auto s = message.GetTypeName();

  if (auto prog = program::getProgram())
    s = prog->mapTypeName(s);

  return s;
}
#endif

}  // namespace util
}  // namespace rec
