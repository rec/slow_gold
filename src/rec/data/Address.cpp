#include "rec/data/Address.h"
#include "rec/data/DataCenter.h"
#include "rec/util/proto/MessageRegistrarAndMaker.h"

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

AddressProto::Scope getScope(const AddressProto& a)  {
  if (a.has_scope())
    return a.scope();
  return getDataCenter()->messageMaker().scope(a.type_name());
}

#if 0
const Address Address::addTypeName(const string& name) const {
  Address result = *this;
  result.set_type_name(name);
  return result;
}

const Address Address::addScope(AddressProto::Scope scope) const {
  Address result = *this;
  result.set_scope(scope);
  return result;
}
#endif

}  // namespace data
}  // namespace rec
