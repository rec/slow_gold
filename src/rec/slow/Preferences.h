#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/AppBase.h"
#include "rec/persist/Copy.h"
#include "rec/slow/Preferences.pb.h"
#include "rec/slow/RecentFiles.h"
#include "rec/proto/Proto.pb.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;

inline Data* prefs() {
  static Data* prefs = persist::getApp()->getData<proto::Preferences>("preferences");
  return prefs;
}

inline void applyOperation(rec::proto::Operation* op) {
  prefs()->change(op);
}

inline const proto::Preferences getPreferences() {
  return prefs()->get();
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
