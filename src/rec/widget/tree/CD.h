#pragma once

#include "rec/music/Metadata.h"
#include "rec/util/cd/CDReader.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/tree/Directory.h"

namespace rec {
namespace widget {
namespace tree {

class CD : public Directory {
  public:
    CD(const NodeDesc& d, const VirtualFile& vf) : Directory(d, vf) {}

    virtual int minPartition() const { return 100; }
    virtual void computeChildren();

  private:
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CD);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

