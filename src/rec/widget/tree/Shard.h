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
  Shard(const NodeDesc& desc, const VolumeFile& file,
        const partition::Shard& shard, FileArray* children)
      : Directory(desc, file), shard_(shard) {
    children_ = children;
    range_ = shard_.range_;
    partition();
  }

  const String computeName() const { return shard_.name_; }

  virtual void requestPartition() {}
  virtual void computeChildren() {}

 private:
  const partition::Shard shard_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Shard);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_SHARD__
