#ifndef __REC_DATA_PERSIST_APPDIRECTORY__
#define __REC_DATA_PERSIST_APPDIRECTORY__

#include "rec/base/base.h"


namespace rec {
namespace data {
namespace persist {

inline const File& appDirectory() {
  static const char COMPANY_NAME[] = "recs";
  static File dd = File::getSpecialLocation(File::userApplicationDataDirectory);
  static File app = dd.getChildFile(COMPANY_NAME);
  return app;
}

}  // namespace persist
}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_APPDIRECTORY__
