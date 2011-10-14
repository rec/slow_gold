#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/data/persist/TypedEditable.h"
#include "rec/util/file/VirtualFile.h"

#include "rec/app/Files.h"

namespace rec {
namespace data {

typedef std::map<string, UntypedEditable*> EditableMap;

void needsUpdate(UntypedEditable*);
void addToUndoQueue(UntypedEditable* u, const OperationQueue& q);

EditableMap* editableMap();
CriticalSection* editableMapLock();

void start();
void stop();

inline const VirtualFile& noFile() { return VirtualFile::default_instance(); }

template <typename Proto>
TypedEditable<Proto>* editable(const VirtualFile& vf = noFile()) {
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
    //editableMap()->insert(make_pair(key, e), i);

    (*editableMap())[key] = e;
  }
  return dynamic_cast<data::TypedEditable<Proto>*>(e);
}

}  // namespace data
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
