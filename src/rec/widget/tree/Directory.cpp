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
      isShard_(false),
      computing_(false),
      computingDone_(false),
      isOpen_(false) {
}

Directory::Directory(const Directory& d, const Range& r)
    : Node(d.desc_, d.shadow_),
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

void Directory::addChildFile(int begin, int end) {
  Node* node;
  bool isShard = ((end - begin) != 1);
  if (isShard) {
    node = new Directory(*this, Range(begin, end));

  } else {
    const File& f = (*children_)[begin];
    ShadowFile sf(f, shadow_.shadow_.getChildFile(f.getFileName()));
    bool isDir = sf.file_.isDirectory();
    node = isDir ? new Directory(desc_, sf) : new Node(desc_, sf);
  }

  node->listeners()->insert(this);
  {
    MessageManagerLock l(thread_.get());
    addSubItem(node);
  }

  if (isOpen_)
    node->requestPartition();
}

void Directory::computeChildren() {
  File f = shadow_.file_;
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  childrenDeleter_.reset(new FileArray);
  children_ = childrenDeleter_.get();
  sortedChildren(f, children_, juce::Thread::getCurrentThread());

  range_.begin_ = 0;
  range_.end_ = children_->size();
  partition();
}

void Directory::partition() {
  ScopedLock l(lock_);
  if (!computingDone_) {
    juce::Array<int> partition;
    partitionChildren(*children_, range_, desc_.best_branch(), &partition);
    for (int i = 0; i < partition.size() - 1; ++i)
      addChildFile(partition[i], partition[i + 1]);

    computingDone_ = computing_ = true;
  }
}

String getSub(const File& f, int letters) {
  String s = f.getFileName().substring(0, letters + 1);
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

  requestPartition();
  for (int i = 0; i < getNumSubItems(); ++i)
    ((Node*) getSubItem(i))->requestPartition();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
