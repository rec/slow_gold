#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/base/base.h"
#include "rec/data/persist/Data.h"
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

  template <typename Proto> Data<Proto>* data(const VirtualFile&);
  virtual void needsUpdate(data::UntypedData* data) = 0;

 private:
  typedef std::map<string, data::Editable*> DataMap;

  CriticalSection lock_;
  DataMap data_;

  DISALLOW_COPY_AND_ASSIGN(App);
};

template <typename Proto>
Data<Proto>* App::data(const VirtualFile& vf) {
  File directory = getShadowDirectory(vf);
  string fileName = data::proto::getName<Proto>();
  string fileKey = str(directory.getFullPathName()) + ("/" + fileName);
  ScopedLock l(lock_);
  DataMap::const_iterator i = data_.find(fileKey);
  if (i != data_.end())
    return static_cast<persist::Data<Proto>*>(i->second);

  File file = directory.getChildFile(str(fileName));
  persist::Data<Proto>* data = new Data<Proto>(file, this);
  data->readFromFile();

  data_[fileKey] = data;
  return data;
}
}  // namespace persist

}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
