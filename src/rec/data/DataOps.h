#pragma once

#include "rec/data/Data.h"
#include "rec/data/Reader.h"
#include "rec/data/Undoable.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

void setProto(const Message&, Undoable undoable = CAN_UNDO);
void setProto(const Message&, Data* data, Undoable undo = CAN_UNDO);
void setProto(const Message&, const VirtualFile&, Undoable undo = CAN_UNDO);

template <typename Proto> const Proto getProto();
template <typename Proto> const Proto getProto(Data* data);
template <typename Proto> const Proto getProto(const VirtualFile& vf);

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

