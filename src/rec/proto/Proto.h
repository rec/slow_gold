#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include <cstdarg>

#include <algorithm>
#include "rec/base/basictypes.h"
#include "rec/base/scoped_ptr.h"
#include "rec/proto/Applier.h"
#include "rec/proto/Proto.pb.h"

// useful functions to deal with protocol buffers.

namespace rec {
namespace proto {

template <typename Container, typename Type>
void moveToEnd(int index, int offset, Container* cont) {
  if (offset) {
    for (; index < cont->size() - offset; ++index)
      cont->SwapElements(index, index + offset);
  }
}

// Returns true if the element were added.
template <typename Container, typename Type>
void addOrMoveToEnd(const Type& value, Container* cont) {
  typename Container::iterator found = std::find(cont->begin(),
                                                 cont->end(), value);
  if (found == cont->end())
    *(cont->Add()) = value;
  else
    moveToEnd<Container, Type>(found - cont->begin(), 1, cont);
}

template <typename Container, typename Type>
void truncateTo(int size, Container* cont, Type t) {
  int offset = cont->size() - size;
  if (offset > 0) {
    moveToEnd<Container, Type>(0, offset, cont);
    for (int i = 0; i != offset; ++i)
      cont->RemoveLast();
  }
}

inline bool applyOperation(const Operation& operation,
                           google::protobuf::Message* msg) {
  scoped_ptr<Applier> applier(Applier::create(operation, msg));
  return applier && applier->apply();
}

inline Operation* createOperation(Operation::Command command, ...) {
  Operation *op = new Operation();
  op->set_command(command);

  va_list ap;
  va_start(ap, command);

  for (uint32 addr = va_arg(ap, uint32); addr; addr = va_arg(ap, uint32))
    op->add_address(addr);

  return op;
}


}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_PROTO
