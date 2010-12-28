#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/gui/DropTarget.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/util/file/VolumeFile.pb.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/util/listener/DataListener.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public Thread,
             public listener::Broadcaster<const VolumeFile&> {
 public:
  explicit Root(const NodeDesc& desc);
  virtual ~Root() {}

  virtual void run();
  void mergeNewIntoOld(const file::VolumeList& volumes);
  TreeView* treeView() { return &tree_; }

 private:
  void update();
  void addVolume(const file::Volume& volume, int insertAt);
  Node* getNode(int i) { return (Node*) root_.getSubItem(i); }
  int getNumNodes() const { return root_.getNumSubItems(); }

  class TreeViewItem : public juce::TreeViewItem {
   public:
    bool mightContainSubItems() { return true; }
  };

  NodeDesc desc_;
  gui::DropTarget<TreeView, String, gui::NullInterface> tree_;
  TreeViewItem root_;
  file::VolumeList volumes_;
  // listener::DataListener<file::VolumeFileList> fileListener_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
  JUCE_LEAK_DETECTOR(Root);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
