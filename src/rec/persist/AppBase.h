#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/base/basictypes.h"
#include "rec/util/STL.h"
#include "rec/persist/Data.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

AppBase* getApp();
class UntypedData;

class AppBase {
 public:
  typedef std::string string;
  typedef std::map<string, UntypedData*> DataMap;

  template <typename Proto>
  Data<Proto>* getData(const string& file) {
    string filename = file + "." + Proto::descriptor()->name();
    ScopedLock l(lock_);
    DataMap::const_iterator i = data_.find(filename);
    if (i == data_.end()) {
      File file = appDir().getChildFile(filename.c_str());
      Data<Proto>* data = new Data<Proto>(file, this);
      data_[filename] = data;
      return data;
    }

    return static_cast<Data<Proto>*>(i->second);
  }

  const string& name() const { return name_; }

  virtual ~AppBase() {
    stl::deleteMapPointers(&data_);
  }

  File appDir() const {
    static const char COMPANY_ROOT_NAME[] = "recs";
    return File::getSpecialLocation(File::userApplicationDataDirectory).
      getChildFile(COMPANY_ROOT_NAME).getChildFile(name_.c_str());
  }

 protected:
  friend class UntypedData;
  explicit AppBase(const string& name) : name_(name) {}

  virtual void needsUpdate(UntypedData* data) = 0;

  DataMap data_;
  CriticalSection lock_;
  const string name_;

  DISALLOW_COPY_AND_ASSIGN(AppBase);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
