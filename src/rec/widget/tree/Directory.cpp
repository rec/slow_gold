#include "rec/widget/tree/Directory.h"

#include "rec/util/cd/Album.h"
#include "rec/util/cd/Album.pb.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/partition/Compare.h"
#include "rec/util/partition/Partition.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/Shard.h"

using namespace juce;

using namespace rec::util::cd;
using namespace rec::thread;

using partition::indexOfDifference;

namespace rec {
namespace widget {
namespace tree {

Directory::Directory(const NodeDesc& d, const VolumeFile& vf)
    : Node(d, vf),
      children_(NULL),
      isOpen_(false) {
}

void Directory::run() {
  computeChildren();
  partition();
}

Node* Directory::createChildFile(int begin, int end) const {
  Node* node;
  if ((end - begin) != 1)
    return new Shard(*this, Range<int>(begin, end));

  const File& f = (*children_)[begin];
  VolumeFile vf(volumeFile_);
  vf.add_path(f.getFileName().toCString());
  bool isDir = getFile(vf).isDirectory();
  return isDir ? new Directory(desc_, vf) : new Node(desc_, vf);
}

void Directory::addChildFile(Node* node) {
  node->addListener(this);
  if (isOpen_)
    node->requestPartition();

  thread::callAsync(this, &Directory::addSubItem, node);
}

void Directory::computeChildren() {
  File f = getFile(volumeFile_);
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  resetChildren();
  sortedChildren(f, children_);
  range_.begin_ = 0;
  range_.end_ = children_->size();
}

void Directory::partition() {
  juce::Array<int> part = partition::partitionList(*children_, range_);
  for (int i = 0; i < part.size() - 1; ++i)
    addChildFile(part[i], part[i + 1]);
}

String getSub(const File& f, int letters) {
  String s = f.getFileName().substring(0, letters + 1);
  s[0] = tolower(s[0]);
  return s;
}

const String Directory::name() const {
  if (name_.length())
    return name_;

  int size = children_->size();
  if (range_.size() == size)
    return Node::name();

  int b = range_.begin_ ? indexOfDifference(*children_, range_.begin_) : 1;
  int e = range_.end_ == size ? 1 : indexOfDifference(*children_, range_.end_);

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
