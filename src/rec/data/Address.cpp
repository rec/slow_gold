#include "rec/data/Address.h"

namespace rec {
namespace data {

const string toString(const Address& x) {
  string s;
  for (int i = 0; i < x.part_size(); ++i) {
    if (i)
      s += ".";
    if (x.part(i).has_name())
      s += x.part(i).name();
    else
      s += str(String(x.part(i).index()));
  }
  return s;
}

}  // namespace data
}  // namespace rec
