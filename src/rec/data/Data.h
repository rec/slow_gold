#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

#include "rec/app/Files.h"
#include "rec/data/TypedEditable.h"
#include "rec/data/Value.h"
#include "rec/util/DefaultRegistry.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

EditableMap* editableMap();
CriticalSection* editableMapLock();

template <typename Proto>
File editableFile(const VirtualFile& vf = file::none());

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf = file::none());

template <typename Proto>
TypedEditable<Proto>* emptyEditable();

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(), bool undoable = true) {
  editable<Proto>(f)->setValue(p, Address::default_instance(), undoable);
}

template <typename Proto>
const Proto get(const VirtualFile& f = file::none());

template <typename Proto>
const Value getValue(const Address&, const VirtualFile& f = file::none());

template <typename Proto, typename Operator>
void apply(Operator);

template <typename Proto, typename Operator>
void apply(const VirtualFile&, Operator);

template <typename Proto, typename Operator, typename Value>
void apply(const VirtualFile&, Operator, Value);

template <typename Proto, typename Operator, typename V1, typename V2>
void apply(const VirtualFile&, Operator, V1, V2);

//
// Implementations
//

template <typename Proto>
File editableFile(const VirtualFile& vf = file::none()) {
  return getShadowFile(vf, str(Proto::default_instance().GetTypeName()));
}

template <typename Proto>
TypedEditable<Proto>* makeEditable(const VirtualFile* vf) {
  File file;
  string key;
  if (vf) {
    file = editableFile<Proto>(*vf);
    key = str(file);
  } else {
    key = ":empty:" + Proto::default_instance().GetTypeName();
  }
  Lock l(*editableMapLock());
  EditableMap::const_iterator i = editableMap()->find(key);
  TypedEditable<Proto>* e;
  if (i == editableMap()->end()) {
    e = vf ? new TypedEditable<Proto>(file, *vf) :
      new EmptyTypedEditable<Proto>();
    (*editableMap())[key] = e;
  } else {
    e = dynamic_cast<TypedEditable<Proto>*>(i->second);
    DCHECK(e);
  }

  return e;
}

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf) {
  return makeEditable<Proto>(&vf);
}

template <typename Proto>
TypedEditable<Proto>* emptyEditable() {
  return makeEditable<Proto>(NULL);
}

template <typename Proto>
void setValue(const Proto& p, const VirtualFile& f, const Address& a, bool undoable) {
  editable<Proto>(f)->setValue(p, a, undoable);
}

template <typename Proto>
const Proto get(const VirtualFile& f) {
  return editable<Proto>(f)->get();
}

template <typename Proto>
const Value getValue(const Address& address, const VirtualFile& f) {
  return editable<Proto>(f)->getValue(address);
}

template <typename Proto>
void apply(const VirtualFile& vf, void (*op)(Proto*)) {
  Proto p(get<Proto>(vf));
  op(&p);
  set(p, vf);
}

template <typename Proto, typename Value>
void apply(const VirtualFile& vf, void (*op)(Proto*, Value), Value v) {
  Proto p(get<Proto>(vf));
  op(&p, v);
  set(p, vf);
}

template <typename Proto, typename V1, typename V2>
void apply(const VirtualFile& vf, void (*op)(Proto*, V1, V2), V1 v1, V2 v2) {
  Proto p(get<Proto>(vf));
  op(&p, v1, v2);
  set(p, vf);
}

template <typename Proto, typename Operator>
void apply(const VirtualFile& vf, Operator op) {
  Proto p(get<Proto>(vf));
  op(&p);
  set(p, vf);
}

template <typename Proto, typename Operator, typename Value>
void apply(const VirtualFile& vf, Operator op, Value v) {
  Proto p(get<Proto>(vf));
  op(&p, v);
  set(p, vf);
}

template <typename Proto, typename Operator, typename V1, typename V2>
void apply(const VirtualFile& vf, Operator op, V1 v1, V2 v2) {
  Proto p(get<Proto>(vf));
  op(&p, v1, v2);
  set(p, vf);
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
