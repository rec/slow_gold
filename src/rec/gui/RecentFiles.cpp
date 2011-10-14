#include <algorithm>

#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"

using namespace std;
using namespace google::protobuf;
using namespace rec::data;

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
  RecentFiles rf = data::get<RecentFiles>();
  google::protobuf::RepeatedPtrField<RecentFile>* recent = rf.mutable_file();
  sort(recent->begin(), recent->end(), CompareRecentFiles());

  return rf;
}

void addRecentFile(const VirtualFile& f) {
  int64 timestamp = juce::Time::currentTimeMillis();
  RecentFiles recent = data::get<RecentFiles>();

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

  pmessage msg(r);

  if (!found && recent.file_size() < recent.max_files())
    data::editable<RecentFiles>()->append(msg, Address("file"));
  else
    data::editable<RecentFiles>()->set(msg, Address("file", slot));
}

}  // namespace gui
}  // namespace rec
