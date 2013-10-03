#include "rec/data/Address.h"
#include "rec/data/DataCenter.h"
#include "rec/util/proto/MessageRegistrarAndMaker.h"

namespace rec {
namespace data {

Address splitAddress(const string& s) {
  Address result;

  StringArray typeAndAddress;
  typeAndAddress.addTokens(str(s), ":", "");
  if (typeAndAddress.size() != 2) {
    LOG(DFATAL) << "Address must have exactly one : in it but is " << s;
  } else {
    result.set_type_name(str(typeAndAddress[0]));
    StringArray addressParts;
    addressParts.addTokens(typeAndAddress[1], ".", "");

    if (not addressParts.size()) {
      LOG(DFATAL) << "Address part is empty: " << s;
    } else {
      for (int i = 0; i < addressParts.size(); ++i) {
        const String& part = addressParts[i];
        auto newPart = result.add_part();
        if (isdigit(part[0]))
          newPart->set_index(part.getIntValue());
        else
          newPart->set_name(str(part));
      }
    }
  }

  return result;
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

  if (getScope() == AddressProto::FILE_SCOPE)
    s += "-file";
  else
    s += "-global";
  return s;
}

AddressProto::Scope Address::getScope() const {
  if (has_scope())
    return scope();
  return getDataCenter()->messageMaker().getScope(type_name());
}

}  // namespace data
}  // namespace rec
