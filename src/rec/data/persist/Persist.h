#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/App.h"

namespace rec {
namespace persist {

inline const VirtualFile& noFile() { return VirtualFile::default_instance(); }

template <typename Proto>
Data<Proto>* setter(const VirtualFile& f = noFile()) {
  return getApp()->data<Proto>(f);
}

template <typename Proto>
const Proto get(const VirtualFile& f = noFile()) {
  return setter<Proto>(f)->get();
}

template <typename Proto>
void set(const Proto& proto, const VirtualFile& f = noFile()) {
  setter<Proto>(f)->set(proto);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
