#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/EditableFactory.h"

namespace rec {
namespace persist {

inline const VirtualFile& noFile() { return VirtualFile::default_instance(); }

EditableFactory* getEditableFactory();

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& f) {
  return getEditableFactory()->get<Proto>(f);
}

template <typename Proto>
TypedEditable<Proto>* editableGlobal() {
  return getEditableFactory()->get<Proto>(noFile());
}

template <typename Proto>
const Proto get(const VirtualFile& f) {
  return editable<Proto>(f)->get();
}

template <typename Proto>
const Proto getGlobal() {
  return editable<Proto>(noFile())->get();
}

template <typename Proto>
void set(const Proto& proto, const VirtualFile& f) {
  data::set(editable<Proto>(f), proto);
}

template <typename Proto>
void setGlobal(const Proto& proto) {
  data::set(editable<Proto>(noFile()), proto);
}

/*
template <typename Proto>
void set(const Proto& p, const VirtualFile& f, const data::Address& a) {
  data::set(editable<Proto>(f), a, p);
}

template <typename Proto>
void setGlobal(const Proto& p, const data::Address& a) {
  data::set(editable<Proto>(noFile()), a, p);
}
*/

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
