#include "rec/data/proto/Field.h"
#include "rec/data/Value.h"
#include "rec/data/proto/NameToProto.h"

namespace rec {
namespace data {

OperationList* applyOperations(const OperationList& list, Message* m) {
  ptr<OperationList> result (new OperationList());
  for (int i = 0; i < list.operation_size(); ++i) {
    const Operation& op = list.operation(i);
    ptr<Field> f(Field::makeField(Address(op.address()), *m));
    if (!f) {
      LOG(ERROR) << "Couldn't perform operation " << op.ShortDebugString();
      return NULL;
    }
    ptr<Operation> undo(f->applyToMessage(op));
    result->add_operation()->CopyFrom(*undo);
  }
  return result.transfer();
}

}  // namespace data
}  // namespace rec
