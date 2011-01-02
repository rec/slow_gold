#include "rec/data/proto/Equals.h"
#include "rec/data/proto/TypedOperations.h"
#include "rec/data/proto/Comparer.h"

namespace rec {
namespace proto {

bool equals(const Message& x, const Message& y, const Comparer& cmp) {
  return typer::equals(x, y, cmp);
}

}  // namespace proto
}  // namespace rec
