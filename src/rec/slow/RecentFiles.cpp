#include "rec/slow/RecentFiles.h"
#include "rec/slow/Preferences.h"
#include "rec/proto/Proto.h"

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
  proto::Preferences prefs = getPreferences();
  RecentFiles* recent = prefs.mutable_recent_files();

  int64 least = timestamp;
  int slot = 0;
  bool found = false;

  for (int i = 0; !found && i < recent->file_size(); ++i) {
    RecentFile* file = recent->mutable_file(i);
    if (file->name() == filename) {
      found = true;
    } else if (file->timestamp() < least) {
      least = file->timestamp();
      slot = i;
    }
  }

  rec::proto::Operation *op;
  if (!found && recent->file_size() < recent->max_files()) {
    op = rec::proto::append(
      rec::proto::Address(slow::proto::Preferences::kRecentFilesFieldNumber,
                          RecentFiles::kFileFieldNumber));
  } else {
    op = rec::proto::set(
      rec::proto::Address(slow::proto::Preferences::kRecentFilesFieldNumber,
                          RecentFiles::kFileFieldNumber,
                          slot));
  }

  RecentFile r;
  r.set_timestamp(timestamp);
  r.set_name(filename);

  rec::proto::addValue(rec::proto::pmessage(r), op);
  applyOperation(op);
}

}  // namespace slow
}  // namespace rec
