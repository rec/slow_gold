#ifndef __REC_PROTO_ADDRESS__
#define __REC_PROTO_ADDRESS__

#include "rec/base/basictypes.h"
#include "rec/proto/Address.pb.h"

namespace rec {
namespace proto {
namespace arg {

struct Address : public proto::Address {
  struct Part : public proto::Address::Part {
    Part(const std::string& s) { set_name(s); }
    Part(const char* s) { set_name(s); }
    Part(int i) { set_index(i); }
    Part(const proto::Address::Part& part) { CopyFrom(part); }
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
};


}  // namespace arg
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_ADDRESS__
