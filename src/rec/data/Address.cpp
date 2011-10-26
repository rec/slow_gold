#include "rec/data/Address.h"

namespace rec {
namespace data {

const Address operator+(const Address& x, const Address& y) {
  Address result = x;
  result.MergeFrom(y);
  return result;
}

const Address operator+(const Address& x, int i) {
  Address result = x;
  result.add_part()->set_index(i);
  return result;
}

const Address operator+(const Address& x, const string& name) {
  Address result = x;
  result.add_part()->set_name(name);
  return result;
}

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
