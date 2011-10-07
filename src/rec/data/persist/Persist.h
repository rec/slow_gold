#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/App.h"

namespace rec {
namespace persist {

inline const VirtualFile& noFile() { return VirtualFile::default_instance(); }

template <typename Proto>
Data<Proto>* setter(const VirtualFile& f) {
  return getApp()->data<Proto>(f);
}

template <typename Proto>
Data<Proto>* setterGlobal() {
  return getApp()->data<Proto>(noFile());
}

template <typename Proto>
const Proto get(const VirtualFile& f) {
  return setter<Proto>(f)->get();
}

template <typename Proto>
const Proto getGlobal() {
  return setter<Proto>(noFile())->get();
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
void set(const data::Address& a, const Proto& p, const VirtualFile& f) {
  data::set(setter<Proto>(f), a, p);
}

template <typename Proto>
void setGlobal(const data::Address& a, const Proto& p) {
  data::set(setter<Proto>(noFile()), a, p);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
