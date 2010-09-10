#ifndef __REC_SLOW_PREFERENCES__
#define __REC_SLOW_PREFERENCES__

#include "rec/persist/AppData.h"
#include "rec/persist/Copy.h"
#include "rec/slow/Preferences.pb.h"

namespace rec {
namespace slow {

typedef persist::Data<proto::Preferences> Data;

inline Data* getMutablePreferences() {
  static Data* data = persist::getAppData<proto::Preferences>("preferences", "");
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
  static const char DEFAULT_THUMBNAIL[] = "\
  background {\
    rgb: 0xFFFFFF\
  }\
  foreground {\
    rgb: 0xADD8E6\
  }";

  LockedPreferences prefs;
  if (!prefs->has_thumbnail())
    persist::copy(std::string(DEFAULT_THUMBNAIL), prefs->mutable_thumbnail());

  return prefs->thumbnail();
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
