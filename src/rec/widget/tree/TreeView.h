#pragma once

#include "rec/util/Disableable.h"
#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/widget/tree/Root.h"

namespace rec {
namespace widget {
namespace tree {

class Root;

class TreeView : public TreeViewDropAll, public Disableable {
 public:
  TreeView() : root_(new Root(this)) {}
  Root* root() { return root_.get(); }

 private:
  unique_ptr<Root> root_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TreeView);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

