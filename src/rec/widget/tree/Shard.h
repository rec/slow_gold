#pragma once

#include "rec/widget/tree/Directory.h"
#include "rec/util/Compare.h"

namespace rec {
namespace widget {
namespace tree {

class Shard : public Directory {
  public:
    Shard(const NodeDesc& desc, const VirtualFile& file,
                const partition::Shard& shard, FileArray* children)
            : Directory(desc, file), shard_(shard) {
        children_ = children;
        range_ = shard_.range_;
        partition();
    }

    String computeName() const { return shard_.name_; }

    virtual void requestChildren() {}
    virtual void computeChildren() {}

  private:
    const partition::Shard shard_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Shard);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

