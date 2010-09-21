#ifndef __REC_PERSIST_APP__
#define __REC_PERSIST_APP__

#include <map>
#include <string>
#include <glog/logging.h>

#include "rec/persist/Data.h"
#include "rec/persist/Writeable.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

class App {
 public:
  App(const String& appName)
      : appDir_(appDir(appName)) {
    CHECK(appName.length());
    appDir_.createDirectory();
  }

  static File appDir(const String& name) {
    static const char COMPANY_ROOT_NAME[] = "recs";
    return File::getSpecialLocation(File::userApplicationDataDirectory).
      getChildFile(COMPANY_ROOT_NAME).getChildFile(name);
  }

  typedef std::map<std::string, Data*> DataSet;

  template <typename Proto>
  TypedData<Proto>* getData(const string& file) {
    string filename = file + "." + Proto::descriptor()->name();
    ScopedLock l(lock_);
    DataSet::const_iterator i = data_.find(filename);
    if (i != data_.end())
      return static_cast<TypedData<Proto>*>(*i);

    Data* client = data_[name];
    File file(appDir.getChildFile(filename.c_str()));

                //          return File(file.getFullPathName() + "." + copy(typeName_));
      const Message* message =
      client.data_ = new Data<Proto>();
      client.descriptor_ = Proto::descriptor();
      return static_cast<Data<Proto>*>(client.data_);
    }
  }

  virtual ~App() {
    write();
    for (DataSet::iterator i = data_.begin(); i != data_.end(); ++i)
      delete i->second.data_;
  }

  File getDataFile(const String& name, const String& type) const {
    return appDir_.getChildFile(name + "." + type);
  }

  const Message* getData(const string& name) const {
    ScopedLock l(lock_);
    return registry_.getData(name);
  }

  bool registerData(const Message* message) {
    ScopedLock l(lock_);
    return registry_.registerData(message);
  }

  // Temporary, see https://github.com/rec/rec/issues/issue/40
  virtual void shutdown() {}

  File dataFileName(const File& file) {
    return File(file.getFullPathName() + "." + copy(typeName_));
  }

  template <typename Proto>
  Data<Proto>* getData(const string& name) {
    ScopedLock l(lock_);
    DataSet::const_iterator i = data_.find(name);

    if (i != data_.end()) {
      const Client& client = i->second;
      CHECK(client.descriptor_ == Proto::descriptor());
      return static_cast<Data<Proto>*>(client.data_);

    } else {
      Client& client = data_[name];
      File file(getDataFile(name.c_str());

                return File(file.getFullPathName() + "." + copy(typeName_));
      const Message* message =
      client.data_ = new Data<Proto>();
      client.descriptor_ = Proto::descriptor();
      return static_cast<Data<Proto>*>(client.data_);
    }
  }

  void write() {
    ScopedLock l(lock_);
    for (DataSet::iterator i = data_.begin(); i != data_.end(); ++i)
      i->second.data_->write();
  }

 private:
  const File appDir_;
  CriticalSection lock_;
  DataRegistry registry_;

  struct Client {
    Writeable* data_;
    const google::protobuf::Descriptor* descriptor_;
  };

  struct Maker {
    const Message* example_;
    Filler filler_;

    Maker(const Message* example, Filler filler = &AppDataRegistry::defaultFill)
        : example_(example),
          filler_(filler) {
    }

    Maker() {}
  };


  typedef std::map<std::string, Client> DataSet;
  DataSet data_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APP__
