#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/base/base.h"
#include "rec/data/persist/Data.h"
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

  virtual ~App();

  command::Manager* commandManager() { return commandManager_; }
  const string& name() const { return name_; }
  File appDir() const;

  template <typename Proto>
  Data<Proto>* getData(const string& fileNameRoot) {
    return getData<Proto>(appDir(), fileNameRoot);
  }

  template <typename Proto>
  Data<Proto>* getData(const VolumeFile& file, const string& fileNameRoot) {
    return getData<Proto>(getShadowDirectory(file), fileNameRoot);
  }

 protected:
  explicit App(const string& name);
  virtual void needsUpdate(UntypedData* data) = 0;

  template <typename Proto>
  Data<Proto>* getData(const File& directory, const string& fileNameRoot) {
    string fileName = getFileName(fileNameRoot, Proto::default_instance());
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

 private:
  friend class UntypedData;

  static string getFileName(const string& nameRoot, const Message& instance);

  DataMap data_;
  CriticalSection lock_;
  const string name_;
  command::Manager* commandManager_;

  DISALLOW_COPY_AND_ASSIGN(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
