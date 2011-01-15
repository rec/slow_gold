#ifndef __REC_DATA_PERSIST_PERSIST__
#define __REC_DATA_PERSIST_PERSIST__

#include "rec/data/persist/App.h"

namespace rec {
namespace persist {

template <typename Proto>
Data<Proto>* data(const VirtualFile& f = VirtualFile::default_instance()) {
  return getApp()->data<Proto>(f);
}

template <typename Proto>
const Proto get(const VirtualFile& f = VirtualFile::default_instance()) {
  return data<Proto>(f)->get();
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_DATA_PERSIST_PERSIST__
