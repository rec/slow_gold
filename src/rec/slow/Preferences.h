#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/AppData.h"
#include "rec/slow/Preferences.pb.h"

namespace rec {
namespace slow {

typedef rec::persist::Data<Preferences> Data;

inline Data* getMutablePreferences() {
  static Data* prefs =
    rec::persist::getAppData<Preferences>("preferences", "");
  return prefs;
}

inline const Preferences getPreferences() { return getMutablePreferences()->get(); }

class LockedPreferences : public Data::Access {
 public:
  LockedPreferences() : Data::Access(getMutablePreferences()) {}

 private:
  DISALLOW_COPY_AND_ASSIGN(LockedPreferences);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
