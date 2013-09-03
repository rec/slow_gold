#include <algorithm>

#include "rec/gui/menu/RecentFiles.h"
#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/music/Metadata.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/Copy.h"

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

void addRecentFile(const VirtualFile& f, const Message& message) {
  if (f.type() == VirtualFile::NONE || f.type() == VirtualFile::CD)
    return;

  int64 timestamp = juce::Time::currentTimeMillis();
  RecentFiles rf = data::getProto<RecentFiles>();
  RecentFile* r = nullptr;
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
  r->mutable_metadata()->CopyFrom(message);
  string s;
  copy::copy(message, &s);
  r->set_metadata_string(s);

  std::sort(rf.mutable_file()->begin(), rf.mutable_file()->end(),
            CompareRecentFiles());
  data::setProto(rf, CANT_UNDO);
}

static const int MAX_DEDUPE_COUNT = 2;

string getMusicTitle(const RecentFile& rf) {
  return music::getTitle(rf.metadata(), rf.file());
}

string getMusicDupeSuffix(const RecentFile& rf, bool isFirst) {
  const music::Metadata& md = rf.metadata();
  string add = isFirst ? md.album_title() : md.artist();
  if (add.size())
    add += ("(" + add + ")");
  return add;
}

vector<string> getRecentFileNames(TitleGetter titleGetter,
                                  DupeSuffixGetter dupeSuffixGetter) {
  RecentFiles rf = data::getProto<RecentFiles>();
  vector<string> results(rf.file_size());
  for (int i = 0; i < rf.file_size(); ++i)
    results[i] = (*titleGetter)(rf.file(i));

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

    for (IntSet::iterator j = dupes.begin(); j != dupes.end(); ++j)
      results[*j] += dupeSuffixGetter(rf.file(*j), i == 0);
  }

  return results;
}

}  // namespace gui
}  // namespace rec