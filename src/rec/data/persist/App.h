#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/data/persist/TypedEditable.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/data/proto/GetProtoName.h"
#include "rec/util/STL.h"

#include "rec/data/persist/AppDirectory.h"

namespace rec {
namespace persist {

App* getApp();

class App {
 public:
  App() {}
  virtual ~App() { stl::deleteMapPointers(&data_); }

  virtual void needsUpdate(data::UntypedEditable* data) = 0;

  template <typename Proto>
  TypedEditable<Proto>* data(const VirtualFile&);

 private:
  typedef std::map<string, data::Editable*> DataMap;

  CriticalSection lock_;
  DataMap data_;

  DISALLOW_COPY_AND_ASSIGN(App);
};

template <typename Proto>
TypedEditable<Proto>* App::data(const VirtualFile& vf) {
  File directory = getShadowDirectory(vf);
  string fileName = data::proto::getName<Proto>();
  string fileKey = str(directory.getFullPathName()) + ("/" + fileName);
  ScopedLock l(lock_);
  DataMap::const_iterator i = data_.find(fileKey);
  if (i != data_.end())
    return static_cast<persist::TypedEditable<Proto>*>(i->second);

  File file = directory.getChildFile(str(fileName));
  TypedEditable<Proto>* data = new TypedEditable<Proto>(file, this);
  data->readFromFile();

  data_[fileKey] = data;
  return data;
}
}  // namespace persist

}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
