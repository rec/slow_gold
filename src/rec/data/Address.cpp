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

}  // namespace data
}  // namespace rec