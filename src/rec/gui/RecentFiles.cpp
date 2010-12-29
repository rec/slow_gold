#include <algorithm>

#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/data/persist/Persist.h"

using namespace std;
using namespace google::protobuf;

namespace rec {
namespace gui {

namespace {

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    // Sort in descending timestamp!
    return x.timestamp() > y.timestamp();
  }
};

}  // namespace

RecentFiles getSortedRecentFiles() {
  RecentFiles rf = persist::get<RecentFiles>();
  google::protobuf::RepeatedPtrField<RecentFile>* recent = rf.mutable_file();
  sort(recent->begin(), recent->end(), CompareRecentFiles());

  return rf;
}

void addRecentFile(const VolumeFile& f) {
  int64 timestamp = juce::Time::currentTimeMillis();
  RecentFiles recent = persist::get<RecentFiles>();

  int64 least = timestamp;
  int slot = 0;
  bool found = false;

  for (int i = 0; !found && i < recent.file_size(); ++i) {
    const RecentFile& file = recent.file(i);
    if (file.file() != f) {
      slot = i;
      found = true;

    } else if (file.timestamp() < least) {
      least = file.timestamp();
      slot = i;
    }
  }

  RecentFile r;
  r.set_timestamp(timestamp);
  r.mutable_file()->CopyFrom(f);

  rec::proto::pmessage msg(r);

  if (!found && recent.file_size() < recent.max_files())
    persist::data<RecentFiles>()->set("file", msg);
  else
    persist::data<RecentFiles>()->set("file", slot, msg);
}

}  // namespace gui
}  // namespace rec
