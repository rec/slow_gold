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
      : appDir_(File::getSpecialLocation(File::userApplicationDataDirectory).
                getChildFile("recs").getChildFile(appName)) {
    CHECK(appName.length());
    appDir_.createDirectory();
  }

  ~App() {
    write();
    for (DataSet::iterator i = data_.begin(); i != data_.end(); ++i)
      delete i->second.data_;
  }

  File getDataFile(const String& name) const {
    return appDir_.getChildFile(name + ".data");
  }

  template <typename Proto>
  Data<Proto>* getData(const std::string& name, const char* initial = "") {
    ScopedLock l(lock_);
    DataSet::const_iterator i = data_.find(name);

    if (i != data_.end()) {
      const DataClient& client = i->second;
      CHECK(client.descriptor_ == Proto::descriptor());
      return static_cast<Data<Proto>*>(client.data_);

    } else {
      DataClient& client = data_[name];
      client.data_ = new Data<Proto>(getDataFile(name.c_str()), initial);
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

  struct DataClient {
    Writeable* data_;
    const google::protobuf::Descriptor* descriptor_;
  };

  typedef std::map<std::string, DataClient> DataSet;
  DataSet data_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APP__
