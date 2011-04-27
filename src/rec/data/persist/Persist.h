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
bool get(Proto* proto, const VirtualFile& f = noFile()) {
  Data<Proto>* data = setter<Proto>(f);
  *proto = data->get();
  return data->fileReadSuccess();
}

template <typename Proto>
const Proto get(const VirtualFile& f = noFile()) {
  Proto p;
  get<Proto>(&p);
  return p;
}

template <typename Proto>
void set(const Proto& proto, const VirtualFile& f = noFile()) {
  setter<Proto>(f)->set(proto);
}

#if 0
// Deprecated from here down.
template <typename Proto>
Data<Proto>* data(const VirtualFile& f) {
  return setter<Proto>(f);
}
#endif

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
