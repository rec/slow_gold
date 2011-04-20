#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/App.h"

namespace rec {
namespace persist {

template <typename Proto>
Data<Proto>* data(const VirtualFile& f) {
  return getApp()->data<Proto>(f);
}

template <typename Proto>
Data<Proto>* appData() {
  return getApp()->appData<Proto>();
}

template <typename Proto>
Data<Proto>* data(const VirtualFile* f) {
  return f ? getApp()->data<Proto>(*f) : NULL;
}

template <typename Proto>
const Proto get(const VirtualFile& f) {
  return data<Proto>(f)->get();
}

template <typename Proto>
const Proto getApp() {
  return appData<Proto>()->get();
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
