#ifndef __REC_DATA_DATAOPS__
#define __REC_DATA_DATAOPS__

#include "rec/util/Proto.h"
#include "rec/data/Opener.h"

namespace rec {
namespace data {

template <typename Proto>
const Proto getProto(Data*);

Message* cloneMessage(Data*);

inline Message* newMessage(Data* data) { return cloneMessage(data); }

void setWithData(Data*, const Message&, Undoable undoable = CAN_UNDO);

// The virtual file for global data (not attached to any specific file).
DataFile global();

// The virtual file for empty data (not stored or updated).
DataFile noData();

void setProto(const Message& m, DataFile vf,
              Undoable undoable = CAN_UNDO);

inline void setProto(const Message& m, const VirtualFile& vf,
                     Undoable undoable = CAN_UNDO) {
  setProto(m, &vf, undoable);
}

inline void set(const Message& m, DataFile vf, Undoable undoable = CAN_UNDO) {
  return setProto(m, vf, undoable);
}

template <typename Proto>
const Proto getProto(DataFile vf);

template <typename Proto>
const Proto getProto(const VirtualFile& vf) { return getProto<Proto>(&vf); }

template <typename Proto>
const Proto get(DataFile vf) {
  return getProto<Proto>(vf);
}

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

inline DataFile global() { return &file::none(); }
inline DataFile noData() { return NULL; }

template <typename Proto>
const Proto getProto(Data* data) {
  return *Reader<Proto>(data);
}

inline Message* cloneMessage(Data* data) {
  return Reader<Message>(data).cloneMessage();
}

inline void setWithData(Data* data, const Message& m, Undoable undoable) {
  Opener<Message>(data, undoable)->CopyFrom(m);
}

inline void setProto(const Message& m, DataFile vf, Undoable undoable) {
  setWithData(getData(getTypeName(m), vf), m, undoable);
}

template <typename Proto>
const Proto getProto(DataFile vf) {
  return getProto<Proto>(getData(getTypeName<Proto>(), vf));
}

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile& vf) {
  function(Opener<Proto>(getData(getTypeName<Proto>(), &vf)).mutable_get());
}

template <typename Proto, typename Functor>
void apply(Functor functor, const VirtualFile& vf) {
  functor(Opener<Proto>(getData(getTypeName<Proto>(), &vf)).mutable_get());
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
