#ifndef __REC_PROTO_ADDRESS__
#define __REC_PROTO_ADDRESS__

#include "rec/data/proto/Address.pb.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

class Address : public AddressProto {
 public:
  Address() {}
  Address(const AddressProto& a) : AddressProto(a) {}

  const string toString() const;
  AddressProto::Scope getScope() const;
};

// Split an address looking like "classname:address" into a full
// address record.
Address splitAddress(const string&);

template <typename Type>
const Address makeAddress() {
  Address a;
  a.set_type_name(getTypeName<Type>());
  return a;
}

template <typename Type>
const Address makeAddress(const string& x) {
  Address a;
  a.set_type_name(getTypeName<Type>());
  a.add_part()->set_name(x);
  return a;
}

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_ADDRESS__
