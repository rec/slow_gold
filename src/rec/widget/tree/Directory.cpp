#include "rec/widget/tree/Directory.h"

#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
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
    thread_.reset(new RunnableThread("LargeDirectory",
                                     makeCallback(this,
                                                  &Directory::computeChildren)));
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

void Directory::addChildFile(Node* node) {
  node->addListener(this);
  if (isOpen_)
    node->requestPartition();

  thread::callAsync(this, &Directory::addNode, node);
}

bool Directory::computeChildren() {
  File f = getFile(volumeFile_);
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return false;
  }

  resetChildren();
  sortedChildren(f, children_);
  range_.begin_ = 0;
  range_.end_ = children_->size();
  partition();
  return true;
}

void Directory::partition() {
  juce::Array<int> part = partition::partitionList(*children_, range_);
  for (int i = 0; i < part.size() - 1; ++i)
    addChildFile(part[i], part[i + 1]);
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
