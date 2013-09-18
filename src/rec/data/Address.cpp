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

const string Address::toString() const {
  string s;
  for (int i = 0; i < part_size(); ++i) {
    if (i)
      s += ".";
    if (part(i).has_name())
      s += part(i).name();
    else
      s += str(String(part(i).index()));
  }

  if (scope() == AddressProto::FILE_SCOPE)
    s += "-file";
  else
    s += "-global";
  return s;
}

const Address Address::addTypeName(const string& name) const {
  Address result = *this;
  result.set_type_name(name);
  return result;
}

}  // namespace data
}  // namespace rec
