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
    setProcessing(true);
    thread_.reset(makeThread("LargeDirectory", this, &Directory::computeChildren));
    thread_->setPriority(desc_.thread_priority());
    thread_->startThread();
  }
}

Node* Directory::createChildFile(const partition::Shard& shard) const {
  if (shard.range_.size() > 1)
    return new Shard(desc(), volumeFile(), shard, children_);

  const File& f = (*children_)[shard.range_.begin_];
  VolumeFile vf(volumeFile_);
  vf.add_path(f.getFileName().toCString());
  bool isDir = getFile(vf).isDirectory();
  return isDir ? new Directory(desc_, vf) : new Node(desc_, vf);
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
  setProcessing(false);
}

void Directory::partition() {
  partition::ShardArray shards = partition::partitionList(*children_, range_,
                                                          minPartition());

  for (int i = 0; i < shards.size() - 1; ++i) {
    ptr<Node> node(createChildFile(shards[i]));
    node->addListener(this);
    if (isOpen_)
      node->requestPartition();

    callAsync(this, &TreeViewItem::addSubItem, node.transfer(), -1);
  }
}

String Directory::getPrefix(const File& f, int letters) {
  return f.getFileName().substring(0, letters + 1).toUpperCase();
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
