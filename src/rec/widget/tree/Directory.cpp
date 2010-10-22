#include <glog/logging.h>

#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/PartitionChildren.h"

namespace rec {
namespace widget {
namespace tree {

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
      addSubItem(isDir ? new Directory(desc_, sf) : new Node(desc_, sf));
    }
  } else {
    juce::Array<int> partition;
    partitionChildren(*children_, range_, desc_.best_branch(), &partition);

    for (int i = 0; i < partition.size() - 1; ++i)
      addSubItem(new Directory(*this, Range(partition[i], partition[i + 1])));
  }
}

String getSub(const File& f, int letters) {
  String s = f.getFileName().substring(0, letters);
  s[0] = toupper(s[0]);
  return s;
}

String Directory::name() const {
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
