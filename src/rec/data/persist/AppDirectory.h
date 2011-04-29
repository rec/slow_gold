#ifndef __REC_DATA_PERSIST_APPDIRECTORY__
#define __REC_DATA_PERSIST_APPDIRECTORY__

#include "rec/base/base.h"

namespace rec {
namespace util {

// Set the name of the application ("SlowGold").  You may only call this once.
void setApplicationName(const String&);
const String& getApplicationName();

// Get the root directory to store files.
File getApplicationDirectory();

inline File getApplicationFile(const String& child) {
  return getApplicationDirectory().getChildFile(child);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_DATA_PERSIST_APPDIRECTORY__
