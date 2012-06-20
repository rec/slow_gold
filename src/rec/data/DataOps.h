#ifndef __REC_DATA_DATAOPS__
#define __REC_DATA_DATAOPS__

#include "rec/data/Opener.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
const Proto getProto(Data*);

template <typename Proto>
void fillProto(Proto*, Data*);

Message* cloneMessage(Data*);

inline Message* newMessage(Data* data) { return cloneMessage(data); }

void setWithData(Data*, const Message&, Undoable undoable = CAN_UNDO);

// The virtual file for global data (not attached to any specific file).
const VirtualFile& global();

// The virtual file for empty data (not stored or updated).
const VirtualFile& noData();

void setProto(const Message& m, const VirtualFile& vf,
              Undoable undoable = CAN_UNDO);

template <typename Proto>
void fillProto(Proto* p, const VirtualFile& vf);

template <typename Proto>
const Proto getProto(const VirtualFile& vf);

template <typename Proto>
const Proto getGlobal() { return getProto<Proto>(global()); }

inline void setGlobal(const Message& m, Undoable undoable = CAN_UNDO) {
  setProto(m, global(), undoable);
}

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile&);

template <typename Proto, typename Functor>
void apply(Functor functor, const VirtualFile&);

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
void fillProto(Proto* proto, Data* data) {
  proto->CopyFrom(*Reader<Proto>(data));
}

template <typename Proto>
void fillProto(Proto* p, const VirtualFile& vf) {
  fillProto(p, getData(getTypeName<Proto>(), vf));
}

template <typename Proto>
const Proto getProto(Data* data) {
  Proto p;
  fillProto(&p, data);
  return p;
}

template <typename Proto>
const Proto getProto(const VirtualFile& vf) {
  return getProto<Proto>(getData(getTypeName<Proto>(), vf));
}

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile& vf) {
  function(Opener<Proto>(getData(getTypeName<Proto>(), vf)).mutable_get());
}

template <typename Proto, typename Functor>
void apply(Functor functor, const VirtualFile& vf) {
  functor(Opener<Proto>(getData(getTypeName<Proto>(), vf)).mutable_get());
}

template <typename Proto>
bool applyToData(bool (*function)(Proto*), Data* data) {
  return function(Opener<Proto>(data).mutable_get());
}

template <typename Proto, typename Functor>
bool applyToData(Functor functor, Data* data) {
  return functor(Opener<Proto>(data).mutable_get());
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAOPS__
