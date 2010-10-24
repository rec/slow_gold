#include <glog/logging.h>

#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/PartitionChildren.h"

namespace rec {
namespace widget {
namespace tree {

Directory::Directory(const NodeDesc& d, const ShadowFile s)
    : Node(d, s), children_(NULL), ready_(false) {
}

Directory::Directory(const Directory& d, const Range& r)
    : Node(d.desc_, d.shadow_), range_(r), children_(d.children_),
      ready_(false) {
}

void Directory::itemOpennessChanged(bool isNowOpen) {
  if (ready_ || !isNowOpen)
    return;

  ready_ = true;
  File f = shadow_.file_;
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  if (!children_) {
    children_ = new FileArray;
    childrenDeleter_.reset(children_);
    sortedChildren(f, children_);
    range_.begin_ = 0;
    range_.end_ = children_->size();
  }

  if (range_.size() <= desc_.max_branch()) {
    for (int i = range_.begin_; i != range_.end_; ++i) {
      const File& f = (*children_)[i];
      ShadowFile sf(f, shadow_.shadow_.getChildFile(f.getFileName()));
      bool isDir = f.isDirectory();
      Node* node = isDir ? new Directory(desc_, sf) : new Node(desc_, sf);
      node->listeners()->insert(this);
      addSubItem(node);
    }
  } else {
    juce::Array<int> partition;
    partitionChildren(*children_, range_, desc_.best_branch(), &partition);

    for (int i = 0; i < partition.size() - 1; ++i) {
      Node* node = new Directory(*this, Range(partition[i], partition[i + 1]));
      node->listeners()->insert(this);
      addSubItem(node);
    }
  }
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
  if (!children_)
    return Node::name();

  int size = children_->size();
  if (range_.size() == size)
    return Node::name();

  int begin = range_.begin_ ? cmpi(*children_, range_.begin_) : 1;
  int end = range_.end_ == size ? 1 : cmpi(*children_, range_.end_);

  String begins = getSub((*children_)[range_.begin_], begin);
  String ends = getSub((*children_)[range_.end_ - 1], end);

  return (begins == ends) ? begins : (begins + " - " + ends);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
