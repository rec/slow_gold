#ifndef __REC_PERSIST_APP__
#define __REC_PERSIST_APP__

#include <set>

#include "rec/persist/Writeable.h"
#include "juce_amalgamated.h"

namespace rec {
namespace persist {

class App {
 public:
  App(const String& appName)
      : appDir_(File::getSpecialLocation(File::userApplicationDataDirectory).
                getChildFile("recs").getChildFile(appName)) {
    appDir_.createDirectory();
  }

  ~App() {
    write();
  }

  File getDataFile(const String& name) const {
    return appDir_.getChildFile(name + ".data");
  }

  void addData(Writeable* data) {
    ScopedLock l(lock_);
    data_.insert(data);
  }

  void removeData(Writeable* data) {
    ScopedLock l(lock_);
    data_.erase(data);
  }

  void write() {
    ScopedLock l(lock_);
    for (DataSet::iterator i = data_.begin(); i != data_.end(); ++i)
      (*i)->write();
  }

 private:
  const File appDir_;
  CriticalSection lock_;

  typedef std::set<Writeable*> DataSet;
  DataSet data_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APP__
