#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include "rec/base/base.h"
#include "rec/data/proto/Address.h"
#include "rec/data/proto/Value.h"

namespace rec {
namespace proto {

class Operation;

Operation* applyOperation(const Operation& operation, Message* msg);
Value getValue(const Address& address, const Message& msg);
bool hasValue(const Address& address, const Message& msg);
int getSize(const Address& address, const Message& msg);

struct ProtoAddress {
  Message* proto_;
  Address address_;

  ProtoAddress() {}
  ProtoAddress(Message* p, const Address& a) : proto_(p), address_(a) {}
  ProtoAddress(const Message& p, const Address& a)
      : proto_(const_cast<Message*>(&p)), address_(a) {
  }

  Value getValue() const;
  bool hasValue() const;
  int getSize() const;
};

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_PROTO
