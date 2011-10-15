#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/EditableFactory.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/util/file/VirtualFile.h"

#include "rec/app/Files.h"

namespace rec {
namespace data {

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf = file::none()) {
  File file = getShadowFile(vf, str(Proto::default_instance().GetTypeName()));
  string key = str(file);
  ScopedLock l(*editableMapLock());
  EditableMap::const_iterator i = editableMap()->find(key);
  UntypedEditable* e;
  if (i != editableMap()->end()) {
    e = i->second;
  } else {
    e = new TypedEditable<Proto>(file, vf);
    e->readFromFile();
    (*editableMap())[key] = e;
  }
  return dynamic_cast<TypedEditable<Proto>*>(e);
}

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(),
         const Address& a = Address::default_instance()) {
  editable<Proto>(f)->set(p, a);
}

template <typename Proto>
const Proto get(const VirtualFile& f = file::none()) {
  return editable<Proto>(f)->get();
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
