#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/base/base.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/VolumeFile.pb.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public juce::TreeView,
             public listener::Broadcaster<const VolumeFile&>,
             public Thread {
 public:
  explicit Root(const NodeDesc& desc);
  virtual ~Root() {}
  virtual void run();

 private:
  void update();
  void addVolume(const Volume& volume, int insertAt);
  Node* getNode(int i) { return (Node*) root_.getSubItem(i); }
  int getNumNodes() const { return root_.getNumSubItems(); }

  class TreeViewItem : public juce::TreeViewItem {
   public:
    bool mightContainSubItems() { return true; }
  };

  NodeDesc desc_;
  TreeViewItem root_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
