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
TypedEditable<Proto>* editable(const VirtualFile& vf = file::none());

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(),
         const Address& a = Address::default_instance());

template <typename Proto>
const Proto get(const VirtualFile& f = file::none());

// Implementations

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf) {
  File file = getShadowFile(vf, str(Proto::default_instance().GetTypeName()));
  string key = str(file);
  ScopedLock l(*editableMapLock());
  EditableMap::const_iterator i = editableMap()->find(key);
  TypedEditable<Proto>* e;
  if (i == editableMap()->end()) {
    e = new TypedEditable<Proto>(file, vf);
    (*editableMap())[key] = e;
  } else {
    e = dynamic_cast<TypedEditable<Proto>*>(i->second);
  }

  return e;
}

template <typename Proto>
void set(const Proto& p, const VirtualFile& f, const Address& a) {
  editable<Proto>(f)->set(p, a);
}

template <typename Proto>
const Proto get(const VirtualFile& f) {
  return editable<Proto>(f)->get();
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
