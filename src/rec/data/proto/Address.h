#ifndef __REC_PROTO_ADDRESS__
#define __REC_PROTO_ADDRESS__

#include "rec/base/base.h"
#include "rec/data/proto/Address.pb.h"

namespace rec {
namespace proto {
namespace arg {

// TODO: fix this name one way or the other.

struct Address : public proto::Address {
  struct Field : public proto::Address::Field {
    Field(const string& s) { set_name(s); }
    Field(const char* s) { set_name(s); }
    Field(int i) { set_index(i); }
    Field(const proto::Address::Field& field) { CopyFrom(field); }
  };

  typedef const Field& P;
  void p(P x) { add_field()->CopyFrom(x); }

  Address() {}
  Address(P a) { p(a); }
  Address(P a, P b) { p(a); p(b); }
  Address(P a, P b, P c) { p(a); p(b); p(c); }
  Address(P a, P b, P c, P d) { p(a); p(b); p(c); p(d); }
  Address(P a, P b, P c, P d, P e) { p(a); p(b); p(c); p(d); p(e); }
  Address(P a, P b, P c, P d, P e, P f) { p(a); p(b); p(c); p(d); p(e); p(f); }
};

}  // namespace arg
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_ADDRESS__
