#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include "rec/base/base.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"

namespace rec {
namespace data {

data::OperationList* applyOperations(const data::OperationList& operations, Message* msg);

data::Value getValue(const data::Address& address, const Message& msg);

bool hasValue(const Address& address, const Message& msg);

int getSize(const Address& address, const Message& msg);

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_PROTO
