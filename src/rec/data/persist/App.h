#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/base/base.h"
#include "rec/data/persist/Data.h"
#include "rec/util/STL.h"
#include "rec/widget/tree/VolumeFile.h"

#include "rec/data/persist/AppDirectory.h"

namespace rec {
namespace command {

class Manager;

}  // namespace command
}  // namespace rec

namespace rec {
namespace persist {

App* getApp();

class UntypedData;

class App {
 public:
  typedef std::map<string, UntypedData*> DataMap;

  template <typename Proto>
  Data<Proto>* getData(const string& fileRoot) {
    return getData<Proto>(appDir(), fileRoot);
  }

  template <typename Proto>
  Data<Proto>* getData(const widget::tree::VolumeFile& file, 
                       const string& fileRoot) {
    return getData<Proto>(getShadowDirectory(file), fileRoot);
  }

 protected:
  template <typename Proto>
  Data<Proto>* getData(const File& directory, const string& fileRoot) {
    string fileName = fileRoot + "." + Proto::descriptor()->name();
    string fileKey = directory.getFullPathName().toCString() + ("/" + fileName);
    ScopedLock l(lock_);
    DataMap::const_iterator i = data_.find(fileKey);
    if (i != data_.end())
      return static_cast<Data<Proto>*>(i->second);

    File file = directory.getChildFile(fileName.c_str());
    Data<Proto>* data = new Data<Proto>(file, this);
    data->readFromFile();
    data_[fileKey] = data;
    return data;
  }

 public:
  command::Manager* commandManager() { return commandManager_; }

  const string& name() const { return name_; }

  virtual ~App() {
    stl::deleteMapPointers(&data_);
  }

  File appDir() const {
    return data::persist::appDirectory().getChildFile(name_.c_str());
  }

 protected:
  friend class UntypedData;
  explicit App(const string& name) : name_(name) {
    appDir().createDirectory();
  }

  virtual void needsUpdate(UntypedData* data) = 0;

  DataMap data_;
  CriticalSection lock_;
  const string name_;
  command::Manager* commandManager_;

  DISALLOW_COPY_AND_ASSIGN(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
