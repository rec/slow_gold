#ifndef __REC_DATA_DATAOPS__
#define __REC_DATA_DATAOPS__

#include "rec/data/Data.h"
#include "rec/data/Reader.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

void setProto(const Message&, Undoable undoable = CAN_UNDO);
void setProto(const Message&, Data* data, Undoable undo = CAN_UNDO);
void setProto(const Message&, const VirtualFile&, Undoable undo = CAN_UNDO);

template <typename Proto> const Proto getProto();
template <typename Proto> const Proto getProto(Data* data);
template <typename Proto> const Proto getProto(const VirtualFile& vf);

// The virtual file for global data (not attached to any specific file).
const VirtualFile& global();

// The virtual file for empty data (not stored or updated).
const VirtualFile& noData();

Message* cloneMessage(Data* data);

// Implementations follow.

template <typename Proto>
const Proto getProto(const VirtualFile& vf) {
  return getProto<Proto>(getData(getTypeName<Proto>(), vf));
}
template <typename Proto>
const Proto getProto(Data* data) {
  Proto proto;
  proto.CopyFrom(*Reader<Proto>(data));
  return proto;
}

template <typename Proto>
const Proto getProto() {
  return getProto<Proto>(global());
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAOPS__
