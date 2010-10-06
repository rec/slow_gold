#ifndef __REC_PROTO_SETTER__
#define __REC_PROTO_SETTER__

#include "rec/base/base.h"
#include "rec/data/proto/Address.h"
#include "rec/data/proto/Value.h"
#include "rec/util/Listener.h"

namespace rec {
namespace proto {
namespace arg {

class Setter {
 public:
  typedef util::Listener<Operation*> Listener;

  Setter(Listener* data) : data_(data) {}

  void append(const Address& address, const Value& value);
  void clear(const Address& address);
  void remove(const Address& address, int itemsToRemove);
  void set(const Address& address, const Value& value);
  void swap(const Address& address, int s1, int s2);

  typedef Address A;
  typedef const A::Field& P;
  typedef const Value& V;

  void append(P a, V v) { return append(A(a), v); }
  void append(P a, P b, V v) { return append(A(a, b), v); }
  void append(P a, P b, P c, V v) { return append(A(a, b, c), v); }
  void append(P a, P b, P c, P d, V v) { return append(A(a, b, c, d), v); }
  void append(P a, P b, P c, P d, P e, V v) { return append(A(a, b, c, d, e), v); }

  void clear(P a) { return clear(A(a)); }
  void clear(P a, P b) { return clear(A(a, b)); }
  void clear(P a, P b, P c) { return clear(A(a, b, c)); }
  void clear(P a, P b, P c, P d) { return clear(A(a, b, c, d)); }
  void clear(P a, P b, P c, P d, P e) { return clear(A(a, b, c, d, e)); }

  void remove(P a, int i)  { return remove(A(a), i); }
  void remove(P a, P b, int i)  { return remove(A(a, b), i); }
  void remove(P a, P b, P c, int i)  { return remove(A(a, b, c), i); }
  void remove(P a, P b, P c, P d, int i)  { return remove(A(a, b, c, d), i); }
  void remove(P a, P b, P c, P d, P e, int i)  { return remove(A(a, b, c, d, e), i); }

  void set(P a, V v) { return set(A(a), v); }
  void set(P a, P b, V v) { return set(A(a, b), v); }
  void set(P a, P b, P c, V v) { return set(A(a, b, c), v); }
  void set(P a, P b, P c, P d, V v) { return set(A(a, b, c, d), v); }
  void set(P a, P b, P c, P d, P e, V v) { return set(A(a, b, c, d, e), v); }

  void swap(P a, int s, int t) { return swap(A(a), s, t); }
  void swap(P a, P b, int s, int t) { return swap(A(a, b), s, t); }
  void swap(P a, P b, P c, int s, int t) { return swap(A(a, b, c), s, t); }
  void swap(P a, P b, P c, P d, int s, int t) { return swap(A(a, b, c, d), s, t); }
  void swap(P a, P b, P c, P d, P e, int s, int t) { return swap(A(a, b, c, d, e), s, t); }

 private:
  Listener* data_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Setter);
};

}  // namespace arg
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_SETTER__
