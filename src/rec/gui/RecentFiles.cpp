#include <algorithm>

#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/Data.h"
#include "rec/data/proto/Equals.h"

using namespace google::protobuf;

namespace rec {
namespace gui {

namespace {

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    return x.timestamp() < y.timestamp();
  }
};

}  // namespace

void addRecentFile(const VirtualFile& f) {
  int64 timestamp = juce::Time::currentTimeMillis();
  RecentFiles rf = data::get<RecentFiles>();
  RecentFile* r = NULL;
  for (int i = 0; i < rf.file_size(); ++i) {
    const RecentFile& file = rf.file(i);
    if (file.file() == f) {
      r = rf.mutable_file(i);
      break;
    }
  }

  if (!r) {
    r = (rf.file_size() < rf.max_files()) ? rf.add_file() :
      rf.mutable_file(0);
  }
  r->set_timestamp(timestamp);
  r->mutable_file()->CopyFrom(f);

  std::sort(rf.mutable_file()->begin(), rf.mutable_file()->end(),
            CompareRecentFiles());

  data::set(rf);
}

}  // namespace gui
}  // namespace rec
