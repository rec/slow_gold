#ifndef __REC_PERSIST_APPBASE__
#define __REC_PERSIST_APPBASE__

#include "rec/base/basictypes.h"
#include "rec/util/STL.h"
#include "rec/persist/TypedData.h"

namespace rec {
namespace persist {

AppBase* getApp();

class AppBase {
 public:
  template <typename Proto>
  static Data<Proto>* getData(const string& file) {
    string filename = file + "." + Proto::descriptor()->name();
    ScopedLock l(lock_);
    DataMap::const_iterator i = data_.find(filename);
    return i == data_.end() ?
      (data_[filename] = new Data<Proto>(File(filename), this)) :
      static_cast<Data<Proto>*>(i->second);
  }

  const string& name() const { return name_; }

  virtual ~AppBase() {
    stl::deleteMapPointers(&data_);
  }

  File appDir() const {
    static const char COMPANY_ROOT_NAME[] = "recs";
    return File::getSpecialLocation(File::userApplicationDataDirectory).
      getChildFile(COMPANY_ROOT_NAME).getChildFile(name_);
  }

 protected:
  friend class Data;
  explicit AppBase(const string& name) : name_(name) {}

  virtual void needsUpdate(Data* data) = 0;

  typedef std::map<std::string, UntypedData*> DataMap;
  DataMap data_;
  CriticalSection lock_;
  const string name_;

  DISALLOW_COPY_AND_ASSIGN(AppBase);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPBASE__
