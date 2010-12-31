#ifndef __REC_WIDGET_TREE_TREEVIEWDROPALL__
#define __REC_WIDGET_TREE_TREEVIEWDROPALL__

#include "rec/gui/DropTarget.h"
#include "rec/util/listener/Listener.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace widget {
namespace tree {

typedef gui::DropTarget<TreeView, String, gui::NullInterface> TreeViewDrop;

class TreeViewDropAll : public TreeViewDrop, public Listener<const VolumeFile&> {
 public:
  TreeViewDropAll();
  virtual void operator()(const VolumeFile& f);
  virtual void paint(Graphics& g);

  bool isInterestedInFileDrag(const StringArray& files);

 private:
  DISALLOW_COPY_AND_ASSIGN(TreeViewDropAll);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREEVIEWDROPALL__
