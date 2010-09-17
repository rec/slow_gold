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
  // TODO: remove this
  return getPreferences().thumbnail();
}

inline void registerPreferences() {
  proto::Preferences* p = new proto::Preferences();
  p->mutable_thumbnail()->mutable_background()->set_rgb(0xFFFFFF);
  p->mutable_thumbnail()->mutable_foreground()->set_rgb(0xADD8E);
  persist::registerData(p);
}

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    // Sort in descending timestamp!
    return x.timestamp() > y.timestamp();
  }
};

inline RecentFiles getSortedRecentFiles() {
  proto::Preferences prefs = getPreferences();
  if (prefs.has_recent_files()) {
    google::protobuf::RepeatedPtrField<RecentFile>* recent =
      prefs.mutable_recent_files()->mutable_file();
    std::sort(recent->begin(), recent->end(), CompareRecentFiles());
  }

  return prefs.recent_files();
}

inline void addRecentFile(const std::string& filename) {
  int64 timestamp = Time::currentTimeMillis();
  LockedPreferences prefs;
  RecentFiles* recent = prefs->mutable_recent_files();

  int64 least = timestamp;
  RecentFile* slot = NULL;
  for (int i = 0; i < recent->file_size(); ++i) {
    RecentFile* file = recent->mutable_file(i);
    if (file->name() == filename) {
      file->set_timestamp(Time::currentTimeMillis());
      return;
    } else if (file->timestamp() < least) {
      least = file->timestamp();
      slot = file;
    }
  }

  if (recent->file_size() < recent->max_files())
    slot = recent->add_file();

  RecentFile r;
  r.set_timestamp(timestamp);
  r.set_name(filename);

  r.Swap(slot);
}

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PREFERENCES__
