#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/App.h"
#include "rec/data/Data.h"

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
void set(const Proto& proto, const VirtualFile& f) {
  data::set(setter<Proto>(f), proto);
}

template <typename Proto>
void setGlobal(const Proto& proto) {
  set(proto, noFile());
}

template <typename Proto>
void set(const Address& a, const Proto& p, const VirtualFile& f = noFile()) {
  data::set(setter<Proto>(f), a, p);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
