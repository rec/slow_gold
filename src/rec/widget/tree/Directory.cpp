#include <glog/logging.h>

#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/Callback.h"
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/PartitionChildren.h"

using rec::thread::RunnableThread;
using rec::thread::makeCallback;
using juce::MessageManagerLock;

namespace rec {
namespace widget {
namespace tree {

Directory::Directory(const NodeDesc& d, const ShadowFile s)
    : Node(d, s),
      children_(NULL),
      thread_(new RunnableThread("LargeDirectory",
                                 makeCallback(this, &Directory::computeChildren))) {
  thread_->setPriority(d.thread_priority());
  thread_->startThread();
}

Directory::Directory(const Directory& d, const Range& r)
    : Node(d.desc_, d.shadow_), range_(r), children_(d.children_) {
}

void Directory::computeChildren() {
  File f = shadow_.file_;
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  FileArray* children = new FileArray;
  sortedChildren(f, children);
  range_.begin_ = 0;
  range_.end_ = children->size();

  if (range_.size() <= desc_.max_branch()) {
    for (int i = range_.begin_; i != range_.end_; ++i) {
      const File& f = (*children)[i];
      ShadowFile sf(f, shadow_.shadow_.getChildFile(f.getFileName()));
      bool isDir = f.isDirectory();
      Node* node = isDir ? new Directory(desc_, sf) : new Node(desc_, sf);
      node->listeners()->insert(this);
      
      MessageManagerLock l(thread_.get());
      addSubItem(node);
    }
  } else {
    juce::Array<int> partition;
    partitionChildren(*children, range_, desc_.best_branch(), &partition);

    for (int i = 0; i < partition.size() - 1; ++i) {
      Node* node = new Directory(*this, Range(partition[i], partition[i + 1]));
      node->listeners()->insert(this);
      MessageManagerLock l(thread_.get());
      addSubItem(node);
    }
  }

  ScopedLock l(lock_);
  children_ = children;
  childrenDeleter_.reset(children_);
}

String getSub(const File& f, int letters) {
  String s = f.getFileName().substring(0, letters);
  s[0] = tolower(s[0]);
  return s;
}

String Directory::name() const {
  {
    ScopedLock l(lock_);
    if (!children_)
      return Node::name();
  }

  int size = children_->size();
  if (range_.size() == size)
    return Node::name();

  int b = range_.begin_ ? indexOfDifference(*children_, range_.begin_) : 1;
  int e = range_.end_ == size ? 1 : indexOfDifference(*children_, range_.end_);

  String begin = getSub((*children_)[range_.begin_], b);
  String end = getSub((*children_)[range_.end_ - 1], e);

  return (begin == end) ? begin : (begin + " - " + end);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
