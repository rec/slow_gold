#ifndef __REC_WIDGET_TREE_SHARD__
#define __REC_WIDGET_TREE_SHARD__

#include "rec/widget/tree/Directory.h"
#include "rec/util/partition/Compare.h"

using rec::util::partition::indexOfDifference;

namespace rec {
namespace widget {
namespace tree {

class Shard : public Directory {
 public:
  Shard(const Directory& d, const Range<int>& r, FileArray* children)
    : Directory(d.desc(), d.volumeFile()) {
      children_ = children;
      range_ = r;
      partition();
  }

  const String computeName() const {
    int size = children_->size();
    if (range_.size() == size)
      return Node::name();

    int b = range_.begin_ ? indexOfDifference(*children_, range_.begin_) : 1;
    int e = range_.end_ == size ? 1 : indexOfDifference(*children_, range_.end_);

    String begin = getSub((*children_)[range_.begin_], b);
    String end = getSub((*children_)[range_.end_ - 1], e);

    return (begin == end) ? begin : (begin + " - " + end);
  }

  virtual void requestPartition() {}
  virtual void computeChildren() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Shard);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_SHARD__
