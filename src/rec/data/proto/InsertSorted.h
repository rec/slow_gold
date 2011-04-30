#ifndef __REC_DATA_PROTO_INSERTSORTED__
#define __REC_DATA_PROTO_INSERTSORTED__

#if 0

#include "rec/base/base.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace proto {

template <typename ProtoList, typename Proto, typename Comparer >
OperationList insertSorted(const ProtoList& list, const Address& addr,
                           const Proto& item, Comparer comparer) {
  int size = getSize(address, list);
  int location = 0;
  for (; location < size; ++location) {
    pmessage pm = getValue(address + location, item);
    Proto locItem;
    if (!pm.Parse(&locItem)) {
      LOG(ERROR) << "Couldn't parse " << address.ShortDebugString()
                 << ", " << location << ", " << item.ShortDebugString();
      continue;
    }
    if (comparer(locItem, item))
      continue;
  }

  OperationList list;
  Operation* op = list->add_operation();
  op->set_type(Operation::APPEND);


  return list;
}


}  // namespace proto
}  // namespace rec

#endif

#endif  // __REC_DATA_PROTO_INSERTSORTED__
