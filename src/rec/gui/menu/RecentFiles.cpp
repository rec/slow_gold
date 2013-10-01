#include <algorithm>

#include "rec/gui/menu/RecentFiles.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/program/Program.h"
#include "rec/program/JuceModel.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/Copy.h"
#include "rec/util/DisableMap.h"

using namespace google::protobuf;

namespace rec {
namespace gui {

namespace {

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    return x.timestamp() > y.timestamp();  // Most recent first.
  }
};

void fixRecentFiles(RecentFiles* rf) {
  for (auto& file: *rf->mutable_file()) {
    if (file.has_metadata()) {
      copy::copy(file.metadata(), file.mutable_metadata_string());
      file.clear_metadata();
    }
  }
}

}  // namespace

void addRecentFile(const VirtualFile& f, const Message& message) {
  if (f.type() == VirtualFile::NONE || f.type() == VirtualFile::CD)
    return;

  int64 timestamp = juce::Time::currentTimeMillis();
  RecentFiles rf = data::getProto<RecentFiles>();
  RecentFile* r = nullptr;
  for (auto& file: *rf.mutable_file()) {
    if (file.file() == f) {
      r = &file;
      break;
    }
  }

  if (!r) {
    r = (rf.file_size() < rf.max_files()) ? rf.add_file() :
      rf.mutable_file(rf.file_size() - 1);
  }
  r->set_timestamp(timestamp);
  r->mutable_file()->CopyFrom(f);
  copy::copy(message, r->mutable_metadata_string());

  std::sort(rf.mutable_file()->begin(), rf.mutable_file()->end(),
            CompareRecentFiles());
  data::setProto(rf, CANT_UNDO);
  program::juceModel()->disableMap()->setProperty("recent_empty", false);
}

static const int MAX_DEDUPE_COUNT = 5;

vector<string> getRecentFileNames() {
  auto& strategy = program::getProgram()->recentFilesStrategy();
  RecentFiles rf = data::getProto<RecentFiles>();
  vector<string> results(rf.file_size());
  for (int i = 0; i < results.size(); ++i)
    results[i] = strategy.getTitle(rf.file(i));

  std::map<string, int> names;
  std::set<int> dupes;

  for (int i = 0; i < MAX_DEDUPE_COUNT; ++i) {
    names.clear();
    dupes.clear();
    for (int j = 0; j < results.size(); ++j) {
      auto f = names.find(results[j]);
      if (f == names.end()) {
        names.insert(f, std::make_pair(results[j], j));
      } else {
        dupes.insert(j);
        dupes.insert(f->second);
      }
    }

    if (dupes.empty())
      break;

    bool first = true;
    for (auto& dupe: dupes) {
      results[dupe] += strategy.getDupeSuffix(rf.file(dupe), first);
      first = false;
    }
  }

  return results;
}

bool recentFilesEmpty() {
  return not data::getProto<RecentFiles>().file_size();
}

}  // namespace gui
}  // namespace rec
