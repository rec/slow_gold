#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/AppData.h"
#include "rec/slow/Preferences.pb.h"

namespace rec {
namespace slow {

inline rec::persist::Data<Preferences>* getPreferences() {
  static rec::persist::Data<Preferences>* prefs = 
    rec::persist::getAppData<Preferences>("preferences", "");
  return prefs;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
