#ifndef __REC_WIDGET_TREE_TREEVIEW__
#define __REC_WIDGET_TREE_TREEVIEW__

#include "rec/gui/DisableableComponent.h"
#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/widget/tree/Root.h"

namespace rec {
namespace widget {
namespace tree {

class Root;

class TreeView : public TreeViewDropAll, public gui::DisableableComponent {
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

#endif  // __REC_WIDGET_TREE_TREEVIEW__
