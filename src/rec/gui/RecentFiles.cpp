#include <algorithm>

#include "rec/gui/RecentFiles.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/Data.h"
#include "rec/data/proto/Equals.h"
#include "rec/music/Metadata.pb.h"
#include "rec/util/file/VirtualFile.h"

using namespace google::protobuf;

namespace rec {
namespace gui {

namespace {

struct CompareRecentFiles {
  bool operator()(const RecentFile& x, const RecentFile& y) {
    return x.timestamp() > y.timestamp();  // Most recent first.
  }
};

}  // namespace

void addRecentFile(const VirtualFile& f, const music::Metadata& metadata) {
  if (empty(f))
    return;

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
      rf.mutable_file(rf.file_size() - 1);
  }
  r->set_timestamp(timestamp);
  r->mutable_file()->CopyFrom(f);
  r->mutable_metadata()->CopyFrom(metadata);

  std::sort(rf.mutable_file()->begin(), rf.mutable_file()->end(),
            CompareRecentFiles());

  data::set(rf);
}

static const int MAX_DEDUPE_COUNT = 2;

std::vector<string> getRecentFileNames() {
  typedef std::vector<string> StrList;

  RecentFiles recent = data::get<RecentFiles>();
  StrList results(recent.file_size());
  for (int i = 0; i < recent.file_size(); ++i) {
    music::Metadata md = recent.file(i).metadata();
    results[i] = "\"" + md.track_title() + "\" - " + md.album_title() +
      " (" + md.artist() + ")";
    if (results[i] == " - ") {
      const VirtualFile f = recent.file(i).file();
      if (f.path_size())
        results[i] = f.path(f.path_size() - 1);
    }
  }

  typedef std::map<string, int> StrMap;
  typedef std::set<int> IntSet;

  StrMap names;
  IntSet dupes;
  for (int i = 0; i < MAX_DEDUPE_COUNT; ++i) {
    names.clear();
    dupes.clear();

    for (uint j = 0; j < results.size(); ++j) {
      StrMap::iterator f = names.find(results[j]);
      if (f == names.end()) {
        names.insert(f, std::make_pair(results[j], j));
      } else {
        dupes.insert(j);
        dupes.insert(f->second);
      }
    }

    if (dupes.empty())
      break;

    for (IntSet::iterator j = dupes.begin(); j != dupes.end(); ++j) {
      const music::Metadata& md = recent.file(*j).metadata();
      string add = (i == 0) ? md.album_title() : md.artist();
      if (add.size())
        results[*j] += ("(" + add + ")");
    }
  }

  return results;
}

}  // namespace gui
}  // namespace rec
