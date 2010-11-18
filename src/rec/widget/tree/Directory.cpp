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

Directory::Directory(const NodeDesc& d, const ShadowFile s, bool startThread)
    : Node(d, s),
      children_(NULL),
      isShard_(false),
      computing_(false),
      computingDone_(false),
      isOpen_(false) {
}

Directory::Directory(const Directory& d, const Range& r, bool startThread)
    : Node(d.desc_, d.shadow_),
      range_(r),
      children_(d.children_),
      isShard_(true),
      computing_(false),
      computingDone_(true),
      isOpen_(false) {
}

Directory::~Directory() {
  ScopedLock l(lock_);
  if (thread_)
    thread_->stopThread(1000);
}

void Directory::startThread() {
  ScopedLock l(lock_);
  if (computing_ || computingDone_ || isShard_)
    return;

  computing_ = true;
  thread_.reset(new RunnableThread("LargeDirectory",
                                   makeCallback(this,
                                                &Directory::computeChildren)));
  thread_->setPriority(desc_.thread_priority());
  thread_->startThread();
}

ShadowFile Directory::getChildShadowFile(int child) {
  const File& f = (*children_)[child];
  return ShadowFile(f, shadow_.shadow_.getChildFile(f.getFileName()));
}

void Directory::computeChildren() {
  File f = shadow_.file_;
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  childrenDeleter_.reset(new FileArray);
  children_ = childrenDeleter_.get();
  sortedChildren(f, children_);

  range_.begin_ = 0;
  range_.end_ = children_->size();

  if (range_.size() <= desc_.max_branch()) {
    for (int i = range_.begin_; i != range_.end_; ++i) {
      ShadowFile sf = getChildShadowFile(i);
      bool isDir = sf.file_.isDirectory();
      Node* node = isDir ? new Directory(desc_, sf) : new Node(desc_, sf);
      node->listeners()->insert(this);

      MessageManagerLock l(thread_.get());
      addSubItem(node);
    }
  } else {
    juce::Array<int> partition;
    partitionChildren(*children_, range_, desc_.best_branch(), &partition);

    for (int i = 0; i < partition.size() - 1; ++i) {
      int p0 = partition[i];
      int p1 = partition[i + 1];
      Node* node = ((p1 - p0) == 1) ? new Directory(*this, Range(p0, p1)) :
        new Node(desc_, getChildShadowFile(p0));
      node->listeners()->insert(this);
      if (isOpen_)
        node->startThread();

      MessageManagerLock l(thread_.get());
      addSubItem(node);
    }
  }

  ScopedLock l(lock_);
  computing_ = false;
  computingDone_ = true;
}

String getSub(const File& f, int letters) {
  LOG(ERROR)
    << "sub: "
    << f.getFileName().toCString() << ", "
    << f.getFileName().toUTF8() << ", "
    << f.getFileName().substring(0, 1).toCString() << ", "
    << f.getFileName().substring(0, 1).toUTF8() << ", ";

  String s = f.getFileName().substring(0, letters);
  s[0] = tolower(s[0]);
  return s;
}

String Directory::name() const {
  if (!isShard_)
    return Node::name();

  int size = children_->size();
  if (range_.size() == size)
    return Node::name();

  int b = range_.begin_ ? indexOfDifference(*children_, range_.begin_) : 1;
  int e = range_.end_ == size ? 1 : indexOfDifference(*children_, range_.end_);

  String begin = getSub((*children_)[range_.begin_], b);
  String end = getSub((*children_)[range_.end_ - 1], e);

  return (begin == end) ? begin : (begin + " - " + end);
}

void Directory::itemOpennessChanged(bool isOpen) {
  isOpen_ = isOpen;
  if (!isOpen)
    return;

  {
    ScopedLock l(lock_);
    if (!computingDone_) {
      if (!computing_)
        startThread();
      return;
    }
  }

  for (int i = 0; i < getNumSubItems(); ++i)
    ((Node*) getSubItem(i))->startThread();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
