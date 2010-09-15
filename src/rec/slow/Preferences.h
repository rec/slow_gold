#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/AppData.h"
#include "rec/persist/Copy.h"
#include "rec/slow/Preferences.pb.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;

inline Data* getMutablePreferences() {
  static Data* data = persist::getAppData<proto::Preferences>("preferences");
  Data::Access prefs(data);

  if (!prefs->loop_window_size())
    prefs->add_loop_window();

  return data;
}

inline const proto::Preferences getPreferences() {
  return getMutablePreferences()->get();
}

class LockedPreferences : public Data::Access {
 public:
  LockedPreferences() : Data::Access(getMutablePreferences()) {}

 private:
  DISALLOW_COPY_AND_ASSIGN(LockedPreferences);
};

inline gui::ThumbnailDescription getThumbnail() {
  return getPreferences().thumbnail();
}

inline void registerPreferences() {
  proto::Preferences* p = new proto::Preferences();
  p->mutable_thumbnail()->mutable_background()->set_rgb(0xFFFFFF);
  p->mutable_thumbnail()->mutable_foreground()->set_rgb(0xADD8E);
  persist::registerData(p);
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
