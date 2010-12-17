#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/base/base.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/VolumeFile.pb.h"
#include "rec/widget/tree/GetVolumes.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public AsyncUpdater,
             public listener::Broadcaster<const VolumeFile&>,
             public Thread {
 public:
  explicit Root(const NodeDesc& desc);
  virtual ~Root() {}
  virtual void run();
  virtual void handleAsyncUpdate();
  TreeView* treeView() { return &tree_; }

 private:
  void update();
  void addVolume(const Volume& volume, int insertAt);
  Node* getNode(int i) { return (Node*) root_.getSubItem(i); }
  int getNumNodes() const { return root_.getNumSubItems(); }

  class TreeViewItem : public juce::TreeViewItem {
   public:
    bool mightContainSubItems() { return true; }
  };

  TreeView tree_;
  TreeViewItem root_;
  NodeDesc desc_;
  VolumeList volumes_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
