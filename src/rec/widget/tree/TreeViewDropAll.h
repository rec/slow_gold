#ifndef __REC_WIDGET_TREE_TREEVIEWDROPALL__
#define __REC_WIDGET_TREE_TREEVIEWDROPALL__

#include "rec/data/Data.h"
#include "rec/gui/DropTarget.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Listener.h"

namespace rec {
namespace widget {
namespace tree {

typedef gui::DropTarget<TreeView, gui::NullInterface> TreeViewDropTarget;

class TreeViewDropAll : public TreeViewDropTarget
#ifdef TREE_VIEW_IS_CUTTABLE
, public Cuttable
#endif
{
 public:
  explicit TreeViewDropAll(MenuBarModel*);
  virtual void paint(Graphics& g);

  bool isInterestedInFileDrag(const StringArray& files);
  bool isTreeDrop(const Component* c) const;

#ifdef TREE_VIEW_IS_CUTTABLE
  virtual bool canCopy() const;
  virtual bool canCut() const { return canCopy(); }
  virtual bool canPaste() const { return true; }
  virtual string copy() const;
  virtual void cut();
  virtual bool paste(const string&);
  const string cuttableName() const { return "Navigator"; }
#endif

  static void registerAllTranslations();

 private:
  ptr<Drawable> slowGoldIcon_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(TreeViewDropAll);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREEVIEWDROPALL__
