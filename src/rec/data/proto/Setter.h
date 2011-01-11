#ifndef __REC_PROTO_SETTER__
#define __REC_PROTO_SETTER__

#include "rec/base/base.h"
#include "rec/data/proto/Address.h"
#include "rec/data/proto/Value.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace proto {
namespace arg {

class Setter : public Listener<Operation*> {
 public:
  Setter() {}

  virtual void operator()(Operation*) = 0;

  void append(const Address& address, const Value& value);
  void clear(const Address& address);
  void remove(const Address& address, int itemsToRemove);
  void set(const Address& address, const Value& value);
  void swap(const Address& address, int s1, int s2);
  virtual const Value get(const Address& address) const = 0;
  virtual bool has(const Address& address) const = 0;
  virtual int getSize(const Address& address) const = 0;

  typedef Address A;
  typedef const A::Field& P;
  typedef const Value& V;
  typedef const Message& M;

  void append(V v) { append(A(), v); }
  void append(P a, V v) { append(A(a), v); }
  void append(P a, P b, V v) { append(A(a, b), v); }
  void append(P a, P b, P c, V v) { append(A(a, b, c), v); }
  void append(P a, P b, P c, P d, V v) { append(A(a, b, c, d), v); }
  void append(P a, P b, P c, P d, P e, V v) { append(A(a, b, c, d, e), v); }

  void append(M m) { append(A(), Value(m)); }
  void append(P a, M m) { append(A(a), Value(m)); }
  void append(P a, P b, M m) { append(A(a, b), Value(m)); }
  void append(P a, P b, P c, M m) { append(A(a, b, c), Value(m)); }
  void append(P a, P b, P c, P d, M m) { append(A(a, b, c, d), Value(m)); }
  void append(P a, P b, P c, P d, P e, M m) { append(A(a, b, c, d, e), Value(m)); }

  void clear() { clear(A()); }
  void clear(P a) { clear(A(a)); }
  void clear(P a, P b) { clear(A(a, b)); }
  void clear(P a, P b, P c) { clear(A(a, b, c)); }
  void clear(P a, P b, P c, P d) { clear(A(a, b, c, d)); }
  void clear(P a, P b, P c, P d, P e) { clear(A(a, b, c, d, e)); }

  void remove(int i)  { remove(A(), i); }
  void remove(P a, int i)  { remove(A(a), i); }
  void remove(P a, P b, int i)  { remove(A(a, b), i); }
  void remove(P a, P b, P c, int i)  { remove(A(a, b, c), i); }
  void remove(P a, P b, P c, P d, int i)  { remove(A(a, b, c, d), i); }
  void remove(P a, P b, P c, P d, P e, int i)  { remove(A(a, b, c, d, e), i); }

  void set(V v) { set(A(), v); }
  void set(P a, V v) { set(A(a), v); }
  void set(P a, P b, V v) { set(A(a, b), v); }
  void set(P a, P b, P c, V v) { set(A(a, b, c), v); }
  void set(P a, P b, P c, P d, V v) { set(A(a, b, c, d), v); }
  void set(P a, P b, P c, P d, P e, V v) { set(A(a, b, c, d, e), v); }

  void set(M m) { set(A(), Value(m)); }
  void set(P a, M m) { set(A(a), Value(m)); }
  void set(P a, P b, M m) { set(A(a, b), Value(m)); }
  void set(P a, P b, P c, M m) { set(A(a, b, c), Value(m)); }
  void set(P a, P b, P c, P d, M m) { set(A(a, b, c, d), Value(m)); }
  void set(P a, P b, P c, P d, P e, M m) { set(A(a, b, c, d, e), Value(m)); }

  void swap(int s, int t) { swap(A(), s, t); }
  void swap(P a, int s, int t) { swap(A(a), s, t); }
  void swap(P a, P b, int s, int t) { swap(A(a, b), s, t); }
  void swap(P a, P b, P c, int s, int t) { swap(A(a, b, c), s, t); }
  void swap(P a, P b, P c, P d, int s, int t) { swap(A(a, b, c, d), s, t); }
  void swap(P a, P b, P c, P d, P e, int s, int t) { swap(A(a, b, c, d, e), s, t); }

  const Value get() const { return get(A()); }
  const Value get(P a) const { return get(A(a)); }
  const Value get(P a, P b) const { return get(A(a, b)); }
  const Value get(P a, P b, P c) const { return get(A(a, b, c)); }
  const Value get(P a, P b, P c, P d) const { return get(A(a, b, c, d)); }
  const Value get(P a, P b, P c, P d, P e) const { return get(A(a, b, c, d, e)); }

  bool has() const { return has(A()); }
  bool has(P a) const { return has(A(a)); }
  bool has(P a, P b) const { return has(A(a, b)); }
  bool has(P a, P b, P c) const { return has(A(a, b, c)); }
  bool has(P a, P b, P c, P d) const { return has(A(a, b, c, d)); }
  bool has(P a, P b, P c, P d, P e) const { return has(A(a, b, c, d, e)); }

 private:
  DISALLOW_COPY_AND_ASSIGN(Setter);
};

}  // namespace arg
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_SETTER__
