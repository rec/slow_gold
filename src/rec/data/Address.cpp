#include "rec/data/Address.h"
#include "rec/data/DataCenter.h"
#include "rec/util/proto/MessageRegistrarAndMaker.h"

namespace rec {
namespace data {

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

  if (getScope(*this) == AddressProto::FILE_SCOPE)
    s += "-file";
  else
    s += "-global";
  return s;
}

AddressProto::Scope getScope(const AddressProto& a)  {
  if (a.has_scope())
    return a.scope();
  return getDataCenter()->messageMaker().getScope(a.type_name());
}

}  // namespace data
}  // namespace rec
