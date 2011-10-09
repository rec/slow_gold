#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include "rec/base/base.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"

namespace rec {
namespace data {

// Apply an operation and return an undo.
OperationList* applyOperations(const OperationList&, Message*);

Value getValue(const Address&, const Message&);
bool hasValue(const Address&, const Message&);
int getSize(const Address&, const Message&);

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_PROTO
