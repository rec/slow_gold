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

  // Split a string address into a typename and a list of parts.
  Address(const string&);

  const string toString() const;
  AddressProto::Scope getScope() const;
};

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
