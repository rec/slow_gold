#ifndef __REC_WIDGET_TREE_TREEVIEWDROPALL__
#define __REC_WIDGET_TREE_TREEVIEWDROPALL__

#include "rec/data/persist/Persist.h"
#include "rec/gui/DropTarget.h"
#include "rec/util/Cuttable.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace widget {
namespace tree {

typedef gui::DropTarget<TreeView, String, gui::NullInterface> TreeViewDropTarget;

class TreeViewDropAll : public TreeViewDropTarget, public Cuttable {
 public:
  TreeViewDropAll();
  virtual void paint(Graphics& g);

  bool isInterestedInFileDrag(const StringArray& files);

  virtual bool canCopy() const;
  virtual bool canPaste() const;
  virtual string copy() const;
  virtual void cut();
  virtual bool paste(const string&) const;
  const string cuttableName() const { return "File Browser"; }

 private:
  DISALLOW_COPY_AND_ASSIGN(TreeViewDropAll);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREEVIEWDROPALL__
