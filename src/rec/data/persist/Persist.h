#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/EditableFactory.h"

namespace rec {

namespace data { class UntypedEditable; }
namespace data { namespace commands { class UndoQueue; }}

namespace persist {

inline const VirtualFile& noFile() { return VirtualFile::default_instance(); }

EditableFactory* getEditableFactory();
data::commands::UndoQueue* getUndoQueue();

template <typename P>
TypedEditable<P>* editable(const VirtualFile& f = noFile()) {
  return getEditableFactory()->get<P>(f);
}

template <typename Proto>
void set(const Proto& p, const VirtualFile& f = noFile(),
         const data::Address& a = data::Address::default_instance()) {
  editable<Proto>(f)->set(p, a);
}

template <typename Proto>
const Proto get(const VirtualFile& f = noFile()) {
  return editable<Proto>(f)->get();
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
