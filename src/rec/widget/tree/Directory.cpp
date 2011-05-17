#include "rec/widget/tree/Directory.h"

#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/Compare.h"
#include "rec/util/partition/Partition.h"
#include "rec/util/file/Util.h"
#include "rec/widget/tree/Shard.h"

using namespace juce;

using namespace rec::thread;

namespace rec {
namespace widget {
namespace tree {

Directory::Directory(const NodeDesc& d, const VirtualFile& vf)
    : Node(d, vf),
      children_(NULL),
      isOpen_(false),
      childrenRequested_(false) {
}

void Directory::requestPartition() {
  ScopedLock l(processingLock_);
  if (!childrenRequested_) {
    processingChildren_.insert(this);
    childrenRequested_ = true;
  }
}

void Directory::itemClicked(const MouseEvent& e) {
  if (!(getParentItem() || !getParentItem()->getParentItem())) {
    topSelection_ = !topSelection_;
    repaintItem();
  }
}

Node* Directory::createChildFile(const partition::Shard& shard) const {
  if (shard.range_.size() > 1)
    return new Shard(desc(), volumeFile(), shard, children_);

  const File& f = (*children_)[shard.range_.begin_];
  VirtualFile vf(volumeFile_);
  vf.add_path(str(f.getFileName()));
  bool isDir = getFile(vf).isDirectory();
  return isDir ? new Directory(desc_, vf) : new Node(desc_, vf);
}

void Directory::computeChildren() {
 File f = getFile(volumeFile_);
  if (f.isDirectory()) {
    resetChildren();
    file::sortedChildren(f, children_);
    range_.begin_ = 0;
    range_.end_ = children_->size();
    partition();
  }
  setProcessing(false);
}

void Directory::partition() {
  partition::ShardArray shards = partition::partitionList(*children_, range_,
                                                          minPartition());

  for (int i = 0; i < shards.size(); ++i) {
    ptr<Node> node(createChildFile(shards[i]));
    listenTo(node.get());
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
  ScopedLock l(lock_);
  isOpen_ = isOpen;
  if (!isOpen)
    return;

  if (!childrenRequested_) {
    requestPartition();
  } else {
    for (int i = 0; i < getNumSubItems(); ++i)
      ((Node*) getSubItem(i))->requestPartition();
  }
}

Directory::NodeSet Directory::processingChildren_;
CriticalSection Directory::processingLock_;

bool Directory::computeBackgroundChildren() {
  Node* node;
  bool result;
  {
    ScopedLock l(processingLock_);
    NodeSet::const_iterator i = processingChildren_.begin();
    if (i == processingChildren_.end())
      return false;

    node = *i;
    processingChildren_.erase(i);
    result = processingChildren_.empty();
  }
  node->computeChildren();

  return result;
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
