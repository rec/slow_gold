#ifndef __REC_DATA_DATAOPS__
#define __REC_DATA_DATAOPS__

#include "rec/util/Proto.h"
#include "rec/data/Opener.h"

namespace rec {
namespace data {

template <typename Proto>
const Proto getFromData(Data* data);

Message* newMessage(Data* data);

void setWithData(Data*, const Message&);

// The virtual file for global data (not attached to any specific file).
const VirtualFile* global();

// The virtual file for empty data (not stored or updated).
const VirtualFile* empty();

Data* getData(const string& typeName, const VirtualFile* vf);

template <typename Proto>
Data* getData(const VirtualFile* vf);

void setProto(const Message& m, const VirtualFile* vf, Undoable undoable = CAN_UNDO);

inline void set(const Message& m, const VirtualFile* vf, Undoable undoable = CAN_UNDO) {
  return setProto(m, vf, undoable);
}

template <typename Proto>
const Proto getProto(const VirtualFile* vf);

template <typename Proto>
const Proto get(const VirtualFile* vf) {
  return getProto<Proto>(vf);
}

template <typename Proto>
const Proto getGlobal() { return getProto<Proto>(global()); }

inline void setGlobal(const Message& m, Undoable undoable = CAN_UNDO) {
  setProto(m, global(), undoable);
}

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile*);

template <typename Proto, typename Functor>
void apply(Functor functor, VirtualFile*);

//
//
//
// Implementations.
//
//
//

inline const VirtualFile* global() { return &file::none(); }
inline const VirtualFile* empty() { return NULL; }

template <typename Proto>
const Proto getProto(Data* data) {
  return *Reader<Proto>(data);
}

inline Message* newMessage(Data* data) {
  return Reader<Message>(data).newMessage();
}

inline void setWithData(Data* data, const Message& m, Undoable undoable) {
  Opener<Message>(data, undoable)->CopyFrom(m);
}

inline Data* getData(const Message& m, const VirtualFile* vf) {
  return getData(getTypeName(m), vf);
}

template <typename Proto>
Data* getData(const VirtualFile* vf) {
  return getData(getTypeName<Proto>(), vf);
}

inline void setProto(const Message& m, const VirtualFile* vf, Undoable undoable) {
  setWithData(getData(getTypeName(m), vf), m, undoable);
}

template <typename Proto>
const Proto getProto(const VirtualFile* vf) {
  return getProto<Proto>(getData(getTypeName<Proto>(), vf));
}

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile* vf) {
  function(Opener<Proto>(getData(getTypeName<Proto>(), vf)).get());
}

template <typename Proto, typename Functor>
void apply(Functor functor, VirtualFile* vf) {
  functor(Opener<Proto>(getData(getTypeName<Proto>(), vf)).get());
}

template <typename Proto>
bool applyToData(bool (*function)(Proto*), Data* data) {
  return function(Opener<Proto>(data).mutable_get());
}

template <typename Proto, typename Functor>
bool applyToData(Functor functor, Data* data) {
  return functor(Opener<Proto>(data).mutable_get());
}

inline void updateClients(Data* data) {
  data->broadcast(*Opener<Message>(data));
}


}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAOPS__
