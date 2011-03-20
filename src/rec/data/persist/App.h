#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/base/base.h"
#include "rec/data/persist/Data.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/data/proto/GetProtoName.h"
#include "rec/util/STL.h"

#include "rec/data/persist/AppDirectory.h"

namespace rec {

namespace command {
class Manager;
}  // namespace command

namespace persist {

App* getApp();

class UntypedData;

class App {
 public:
  typedef std::map<string, UntypedData*> DataMap;

  virtual ~App() { stl::deleteMapPointers(&data_); }

  command::Manager* commandManager() { return commandManager_; }
  const string& name() const { return name_; }

  template <typename Proto>
  Data<Proto>* data(const VirtualFile& file = VirtualFile::default_instance);

  File appDir() const {
    return appDir_.getChildFile(name_.c_str());
  }

 protected:
  explicit App(const string& name) : name_(name) {
    static const char COMPANY_NAME[] = "World Wide Woodshed";
    File dd = File::getSpecialLocation(File::userApplicationDataDirectory);
    appDir_ = dd.getChildFile(COMPANY_NAME);
  }

  virtual void needsUpdate(UntypedData* data) = 0;

 private:
  friend class UntypedData;

  DataMap data_;
  CriticalSection lock_;
  const string name_;
  File appDir_;
  command::Manager* commandManager_;

  DISALLOW_COPY_AND_ASSIGN(App);
};

template <typename Proto>
Data<Proto>* App::data(const VirtualFile& vf) {
  File directory = empty(vf) ? appDir() : getShadowDirectory(vf);

  string fileName = data::proto::getName<Proto>();
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
}  // namespace persist

}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
