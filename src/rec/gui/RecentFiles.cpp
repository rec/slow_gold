#include "rec/gui/RecentFiles.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace gui {

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    // Sort in descending timestamp!
    return x.timestamp() > y.timestamp();
  }
};

RecentFiles getSortedRecentFiles() {
  slow::proto::Preferences prefs = slow::getPreferences();
  if (prefs.has_recent_files()) {
    google::protobuf::RepeatedPtrField<RecentFile>* recent =
      prefs.mutable_recent_files()->mutable_file();
    std::sort(recent->begin(), recent->end(), CompareRecentFiles());
  }

  return prefs.recent_files();
}

void addRecentFile(const string& filename) {
  int64 timestamp = juce::Time::currentTimeMillis();
  slow::proto::Preferences pref = slow::getPreferences();
  RecentFiles* recent = pref.mutable_recent_files();

  int64 least = timestamp;
  int slot = 0;
  bool found = false;

  for (int i = 0; !found && i < recent->file_size(); ++i) {
    RecentFile* file = recent->mutable_file(i);
    if (file->name() == filename) {
      slot = i;
      found = true;

    } else if (file->timestamp() < least) {
      least = file->timestamp();
      slot = i;
    }
  }


  RecentFile r;
  r.set_timestamp(timestamp);
  r.set_name(filename);

  rec::proto::pmessage msg(r);

  if (!found && recent->file_size() < recent->max_files())
    slow::prefs()->setter()->append("recent_files", "file", msg);
  else
    slow::prefs()->setter()->set("recent_files", "file", slot, msg);
}

}  // namespace gui
}  // namespace rec
