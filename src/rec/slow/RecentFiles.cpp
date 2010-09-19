#include "rec/slow/RecentFiles.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace slow {

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    // Sort in descending timestamp!
    return x.timestamp() > y.timestamp();
  }
};

RecentFiles getSortedRecentFiles() {
  proto::Preferences prefs = getPreferences();
  if (prefs.has_recent_files()) {
    google::protobuf::RepeatedPtrField<RecentFile>* recent =
      prefs.mutable_recent_files()->mutable_file();
    std::sort(recent->begin(), recent->end(), CompareRecentFiles());
  }

  return prefs.recent_files();
}

void addRecentFile(const std::string& filename) {
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
