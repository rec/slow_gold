#ifndef __REC_PERSIST_APPLICATION_DATA__
#define __REC_PERSIST_APPLICATION_DATA__

#include "rec/base/base.h"
#include "rec/persist/Copy.h"
#include "rec/persist/Persist.h"

#include "juce_amalgamated.h"

namespace rec {
namespace persist {

File getAppDataFile(const String& name) {
  File dir = File::getSpecialLocation(File::userApplicationDataDirectory);
  return dir.getChildFile("recs/" + name + ".data");
}

template <typename Data>
class ApplicationData : public Persistent<Data, File*> {
 public:
  ApplicationData() {}

  void readFile(const String& name) {
    file_ = getAppDataFile(name);
    Persistent<Data, File>::read(&file_);
  }

  typedef class Persistent<Data, File*>::Accessor Accesssor;

 private:
  File file_;
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPLICATION_DATA__
