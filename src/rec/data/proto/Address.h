#ifndef __REC_PROTO_ADDRESS__
#define __REC_PROTO_ADDRESS__

#include "rec/base/base.h"
#include "rec/data/proto/Address.pb.h"

namespace rec {
namespace proto {
namespace arg {

struct Address : public proto::Address {
  struct Part : public proto::Address::Part {
    Part(const string& s) { set_name(s); }
    Part(const char* s) { set_name(s); }
    Part(int i) { set_index(i); }
    Part(const proto::Address::Part& field) { CopyFrom(field); }
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

  Address(const proto::Address a) : proto::Address(a) {}
};

}  // namespace arg

const Address operator+(const Address& x, const Address& y);
const Address operator+(const Address& x, int i);
const Address operator+(const Address& x, const string& name);

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_ADDRESS__
