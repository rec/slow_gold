#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

#include "rec/data/Value.h"
#include "rec/data/persist/EditableFactory.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/util/file/VirtualFile.h"

#include "rec/app/Files.h"

namespace rec {
namespace data {

// TODO: dflt idea is not correct - remove and instead register defaults very
// early.

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf = file::none(),
                               const Proto& dflt = Proto::default_instance()) {
  File file = getShadowFile(vf, str(Proto::default_instance().GetTypeName()));
  string key = str(file);
  ScopedLock l(*editableMapLock());
  EditableMap::const_iterator i = editableMap()->find(key);
  TypedEditable<Proto>* e;
  if (i == editableMap()->end())
    (*editableMap())[key] = (e = new TypedEditable<Proto>(file, vf, dflt));
  else
    e = dynamic_cast<TypedEditable<Proto>*>(i->second);

  return e;
}

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(),
         const Address& a = Address::default_instance(),
         const Proto& dflt = Proto::default_instance()) {
  editable<Proto>(f, dflt)->set(p, a);
}

template <typename Proto>
const Proto get(const VirtualFile& f = file::none(),
                const Proto& dflt = Proto::default_instance()) {
  return editable<Proto>(f, dflt)->get();
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
