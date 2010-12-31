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
  TreeViewDropAll() : TreeViewDrop("Tree") {
    dropBroadcaster()->addListener(this);
  }

  virtual void operator()(const VolumeFile& f) {
    persist::data<file::VolumeFileList>()->append("file", f);
  }

  virtual void paint(Graphics& g) {
    TreeView::paint(g);
    if (!(getRootItem() && getRootItem()->getNumSubItems())) {
      g.setFont(14.0f);
      static const int HEIGHT = 10;
      g.drawFittedText("Drop directories and files here, or",
                       0, 0, getWidth(), getHeight() - HEIGHT,
                       juce::Justification::centred, 0);

      g.drawFittedText("click to add directories and files.",
                       0, HEIGHT, getWidth(), getHeight(),
                       juce::Justification::centred, 0);
    }
  }

  bool isInterestedInFileDrag(const StringArray& files) {
    for (int i = 0; i < files.size(); ++i) {
      if (file::isAudio(files[i]) || File(files[i]).isDirectory())
        return true;
    }
    return false;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(TreeViewDropAll);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREEVIEWDROPALL__
