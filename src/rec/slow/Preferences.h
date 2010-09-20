#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/AppData.h"
#include "rec/persist/Copy.h"
#include "rec/slow/Preferences.pb.h"
#include "rec/slow/RecentFiles.h"
#include "rec/proto/Proto.pb.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;

inline Data* getMutablePreferences() {
  return persist::getAppData<proto::Preferences>("preferences");
}

inline void applyOperation(rec::proto::Operation* op) {
  getMutablePreferences()->apply(op);
}

inline const proto::Preferences getPreferences() {
  return getMutablePreferences()->get();
}

inline void registerPreferences() {
  proto::Preferences* p = new proto::Preferences();
  p->mutable_thumbnail()->mutable_background()->set_rgb(0xFFFFFF);
  p->mutable_thumbnail()->mutable_foreground()->set_rgb(0xADD8E);
  p->add_loop_window();
  persist::registerData(p);
}


}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
