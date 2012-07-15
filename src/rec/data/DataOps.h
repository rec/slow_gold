#ifndef __REC_DATA_DATAOPS__
#define __REC_DATA_DATAOPS__

#include "rec/data/Data.h"
#include "rec/data/Opener.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
const Proto getProto(Data*);

template <typename Proto>
const Proto getProto(const VirtualFile& vf);

Message* cloneMessage(Data*);

void setWithData(Data*, const Message&, Undoable undoable = CAN_UNDO);

// The virtual file for global data (not attached to any specific file).
const VirtualFile& global();

// The virtual file for empty data (not stored or updated).
const VirtualFile& noData();

void setProto(const Message& m, const VirtualFile& vf,
              Undoable undoable = CAN_UNDO);

template <typename Proto>
const Proto getGlobal() { return getProto<Proto>(global()); }

inline void setGlobal(const Message& m, Undoable undoable = CAN_UNDO) {
  setProto(m, global(), undoable);
}


//
//
//
// Implementations.
//
//
//

inline Message* cloneMessage(Data* data) {
  return Reader<Message>(data).cloneMessage();
}

inline void setWithData(Data* data, const Message& m, Undoable undoable) {
  Opener<Message>(data, undoable)->CopyFrom(m);
}

inline void setProto(const Message& m, const VirtualFile& vf, Undoable undoable) {
  setWithData(getData(getTypeName(m), vf), m, undoable);
}

template <typename Proto>
const Proto getProto(Data* data) {
  Proto proto;
  proto.CopyFrom(*Reader<Proto>(data));
  return proto;
}

template <typename Proto>
const Proto getProto(const VirtualFile& vf) {
  return getProto<Proto>(getData(getTypeName<Proto>(), vf));
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAOPS__
