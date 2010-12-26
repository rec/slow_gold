#include "rec/widget/tree/Directory.h"

#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/partition/Compare.h"
#include "rec/util/partition/Partition.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/Shard.h"

using namespace juce;

using namespace rec::thread;

using rec::util::partition::indexOfDifference;

namespace rec {
namespace widget {
namespace tree {

Directory::Directory(const NodeDesc& d, const VolumeFile& vf)
    : Node(d, vf),
      children_(NULL),
      isOpen_(false) {
}

void Directory::requestPartition() {
  ScopedLock l(lock_);
  if (!thread_) {
    thread_.reset(makeThread("LargeDirectory", this, &Directory::computeChildren));
    thread_->setPriority(desc_.thread_priority());
    thread_->startThread();
  }
}

Node* Directory::createChildFile(int begin, int end) const {
  if ((end - begin) != 1)
    return new Shard(*this, Range<int>(begin, end), children_);

  const File& f = (*children_)[begin];
  VolumeFile vf(volumeFile_);
  vf.add_path(f.getFileName().toCString());
  bool isDir = getFile(vf).isDirectory();
  return isDir ? new Directory(desc_, vf) : new Node(desc_, vf);
}

void Directory::addNode(Node* node) {
  DLOG(INFO) << "Adding a node " << getFullDisplayName(node->volumeFile()).toCString();
  addSubItem(node);
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
  partition();
}

void Directory::partition() {
  juce::Array<int> part = partition::partitionList<Array<int> >
      (*children_, range_, minPartition());

  for (int i = 0; i < part.size() - 1; ++i) {
    ptr<Node> node(createChildFile(part[i], part[i + 1]));
    node->addListener(this);
    if (isOpen_)
      node->requestPartition();

    DLOG(INFO) << "ABOUT TO add a node " << getFullDisplayName(node->volumeFile()).toCString();
    callAsync(this, &Directory::addNode, node.transfer());
  }
}

String Directory::getSub(const File& f, int letters) {
  String s = f.getFileName().substring(0, letters + 1);
  s[0] = tolower(s[0]);
  return s;
}

void Directory::resetChildren() {
  childrenDeleter_.reset(new FileArray);
  children_ = childrenDeleter_.get();
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
