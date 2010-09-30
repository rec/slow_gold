#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/App.h"
#include "rec/slow/Preferences.pb.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;

inline Data* prefs() {
  static Data* prefs = persist::getApp()->getData<proto::Preferences>("preferences");
  return prefs;
}

inline const proto::Preferences getPreferences() {
  return prefs()->get();
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
