#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

#include "rec/app/Files.h"
#include "rec/data/TypedEditable.h"
#include "rec/data/Value.h"
#include "rec/util/DefaultRegistry.h"
#include "rec/data/DataRegistry.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

UntypedEditable* editable(const string& typeName,
                          const VirtualFile* vf);

File editableFile(const string& typeName, const VirtualFile* vf);

const string emptyTypeName();

// TODO: get rid of this.
template <typename Proto>
File editableFile(const VirtualFile& vf = file::none()) {
  return editableFile(Proto::default_instance().GetTypeName(), &vf);
}

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile* vf) {
  const string& typeName = Proto::default_instance().GetTypeName();
  return dynamic_cast<TypedEditable<Proto>*>(editable(typeName, vf));
}

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf = file::none()) {
  return editable<Proto>(&vf);
}

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(),
         bool undoable = true) {
  editable<Proto>(f)->setValue(p, Address::default_instance(), undoable);
}

template <typename Proto>
void setValue(const Proto& p, const VirtualFile& f, const Address& a, bool undoable) {
  editable<Proto>(f)->setValue(p, a, undoable);
}

template <typename Proto>
const Proto get(const VirtualFile& f = file::none()) {
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
