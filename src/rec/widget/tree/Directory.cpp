#include "rec/widget/tree/Directory.h"

#include "rec/util/cd/Album.h"
#include "rec/util/cd/Album.pb.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/partition/Compare.h"
#include "rec/util/partition/Partition.h"
#include "rec/widget/tree/SortedChildren.h"

using namespace juce;

using namespace rec::util::cd;
using namespace rec::thread;

namespace rec {
namespace widget {
namespace tree {

Directory::Directory(const NodeDesc& d, const VolumeFile& vf)
    : Node(d, vf),
      children_(NULL),
      isShard_(false),
      computing_(false),
      computingDone_(false),
      isOpen_(false) {
}

Directory::Directory(const Directory& d, const Range<int>& r)
    : Node(d.desc_, d.volumeFile_),
      range_(r),
      children_(d.children_),
      isShard_(true),
      computing_(false),
      computingDone_(false),
      isOpen_(false) {
}

Directory::~Directory() {
  ScopedLock l(lock_);
  if (thread_)
    thread_->stopThread(10000);
}

void Directory::requestPartition() {
  ScopedLock l(lock_);
  if (computing_ || computingDone_) {
    return;

  } else if (isShard_) {
    computing_ = true;
    partition();

  } else {
    computing_ = true;
    thread_.reset(new RunnableThread("LargeDirectory",
                                     makeCallback(this,
                                                  &Directory::computeChildren)));
    thread_->setPriority(desc_.thread_priority());
    thread_->startThread();
  }
}

Node* Directory::createChildFile(int begin, int end) {
  Node* node;
  bool isShard = ((end - begin) != 1);
  if (isShard) {
    node = new Directory(*this, Range<int>(begin, end));

  } else {
    const File& f = (*children_)[begin];
    VolumeFile vf(volumeFile_);
    vf.add_path(f.getFileName().toCString());
    bool isDir = getFile(vf).isDirectory();
    node = isDir ? new Directory(desc_, vf) : new Node(desc_, vf);
  }
  return node;
}

void Directory::addSubItems() {
  NodeSet nodes;
  {
    ScopedLock l(lock_);
    nodes.swap(nodesToAdd_);
  }

  for (NodeSet::iterator i = nodes.begin(); i != nodes.end(); ++i)
    addSubItem(*i);
}

void Directory::addChildFile(Node* node) {
  node->addListener(this);
  if (isOpen_)
    node->requestPartition();

  {
    ScopedLock l(lock_);
    nodesToAdd_.insert(node);
  }
  thread::callAsync(this, &Directory::addSubItems);
}

bool Directory::computeChildren() {
  if (type() == Volume::CD)
    computeCDChildren();
  else
    computeFileChildren();
  return true;
}

void Directory::computeCDChildren() {
  string name = "<Unknown>";
  std::vector<string> tracks;

  const string& cdKey = volumeFile_.volume().name();
  ptr<AudioCDReader> reader(getAudioCDReader(cdKey.c_str()));
  if (reader) {
    TrackOffsets trackOffsets = reader->getTrackOffsets();
    Album album = getAlbum(volumeFile_, trackOffsets);
    if (!album.track_size()) {
      int audioTracks = getAudioTrackCount(*reader);
      for (int i = 0; i < audioTracks; ++i)
        tracks.push_back(String(i).toCString());

    } else {
      name = album.title() + " / " + album.artist();
      for (int i = 0; i < album.track_size(); ++i) {
        const Track& track = album.track(i);
        tracks.push_back(track.artist().empty() ? track.title() :
                         track.artist() + " / " + track.title());
      }
    }
  } else {
    LOG(ERROR) << "Tried to computeCDChildren but no reader";
  }

  resetChildren();
  name_ = name.c_str();

  VolumeFile vf(volumeFile_);
  string* path = vf.add_path();
  for (int i = 0; i < tracks.size(); ++i) {
    *path = String(i).toCString();
    addChildFile(new Node(desc_, vf, tracks[i].c_str()));
  }

  computingDone_ = computing_ = true;
}

void Directory::computeFileChildren() {
  File f = getFile(volumeFile_);
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  resetChildren();
  sortedChildren(f, children_);

  range_.begin_ = 0;
  range_.end_ = children_->size();
  partition();
}

void Directory::partition() {
  ScopedLock l(lock_);
  if (!computingDone_) {
    juce::Array<int> part = partition::partitionList(*children_, range_);
    for (int i = 0; i < part.size() - 1; ++i)
      addChildFile(part[i], part[i + 1]);

    computingDone_ = computing_ = true;
  }
}

String getSub(const File& f, int letters) {
  String s = f.getFileName().substring(0, letters + 1);
  s[0] = tolower(s[0]);
  return s;
}

const String Directory::name() const {
  if (name_.length())
    return name_;

  if (!isShard_)
    return Node::name();

  int size = children_->size();
  if (range_.size() == size)
    return Node::name();

  int b = range_.begin_ ? partition::indexOfDifference(*children_, range_.begin_) : 1;
  int e = range_.end_ == size ? 1 : partition::indexOfDifference(*children_, range_.end_);

  String begin = getSub((*children_)[range_.begin_], b);
  String end = getSub((*children_)[range_.end_ - 1], e);

  name_ = (begin == end) ? begin : (begin + " - " + end);
  return name_;
}

void Directory::itemOpennessChanged(bool isOpen) {
  isOpen_ = isOpen;
  if (!isOpen)
    return;

  requestPartition();
  for (int i = 0; i < getNumSubItems(); ++i)
    ((Node*) getSubItem(i))->requestPartition();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
