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

// TODO: get rid of this, it makes no sense - the first operation should be
// a Message, not a Proto.
template <typename Proto>
void setValue(const Proto& p, const VirtualFile& f, const Address& a);

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none()) {
  setValue<Proto>(p, f, Address::default_instance());
}

template <typename Proto>
const Proto get(const VirtualFile& f = file::none());

template <typename Proto>
const Value getValue(const Address&, const VirtualFile& f = file::none());

//
// Implementations
//

template <typename Proto>
File editableFile(const VirtualFile& vf = file::none()) {
  return getShadowFile(vf, str(Proto::default_instance().GetTypeName()));
}

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf) {
  File file = editableFile<Proto>(vf);
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
void setValue(const Proto& p, const VirtualFile& f, const Address& a) {
  editable<Proto>(f)->setValue(p, a);
}

template <typename Proto>
const Proto get(const VirtualFile& f) {
  return editable<Proto>(f)->get();
}

template <typename Proto>
const Value getValue(const Address& address, const VirtualFile& f) {
  return editable<Proto>(f)->getValue(address);
}


}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
