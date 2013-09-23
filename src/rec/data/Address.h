#ifndef __REC_PROTO_ADDRESS__
#define __REC_PROTO_ADDRESS__

#include "rec/data/proto/Address.pb.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

class Address : public AddressProto {
 public:
  struct Part : public AddressProto::Part {
    Part(const string& s) { set_name(s); }
    Part(const char* s) { set_name(s); }
    Part(int i) { set_index(i); }
    Part(const AddressProto::Part& field) { CopyFrom(field); }

   private:
    JUCE_LEAK_DETECTOR(Part)
  };

  typedef const Part& P;
  void p(P x) { add_part()->CopyFrom(x); }

  Address() {}
  Address(P a) { p(a); }
  Address(P a, P b) { p(a); p(b); }
  Address(P a, P b, P c) { p(a); p(b); p(c); }
  Address(P a, P b, P c, P d) { p(a); p(b); p(c); p(d); }
  Address(P a, P b, P c, P d, P e) { p(a); p(b); p(c); p(d); p(e); }
  Address(P a, P b, P c, P d, P e, P f) { p(a); p(b); p(c); p(d); p(e); p(f); }

  Address(const AddressProto& a) : AddressProto(a) {}
  Address(const string& s) { p(s); }
  Address(const char* s) { p(s); }
  Address(int i) { p(i); }

  const string toString() const;
};

AddressProto::Scope getScope(const AddressProto&) ;

template <typename Type>
const Address makeAddress(const Address::Part& x) {
  Address a(x);
  a.set_type_name(getTypeName<Type>());
  return a;
}

template <typename Type>
const Address makeAddress(const Address::Part& x, const Address::Part& y) {
  Address a(x, y);
  a.set_type_name(getTypeName<Type>());
  return a;
}

// Isn't perhaps only the first one necessary?
inline const Address operator+(const Address& x, const Address& y) {
  Address result = x;
  result.MergeFrom(y);
  return result;
}

inline const Address operator+(int x, const Address& y) {
  return Address(x) + y;
}

inline const Address operator+(const string& x, const Address& y) {
  return Address(x) + y;
}

inline const Address operator+(const char* x, const Address& y) {
  return Address(x) + y;
}

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_ADDRESS__
