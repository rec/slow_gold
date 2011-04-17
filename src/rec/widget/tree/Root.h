#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/widget/tree/NodeItem.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/widget/tree/TreeViewDropAll.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public Thread,
             public Broadcaster<const VirtualFile&>,
             public Listener<const file::VirtualFileList&>,
             public Listener<const VirtualFile&>,
             public juce::MouseListener {
 public:
  explicit Root(const NodeDesc& desc = NodeDesc::default_instance());
  virtual ~Root() {}

  virtual void run();
  void mergeNewIntoOld(const util::file::VirtualFileList& volumes);
  TreeView* treeView() { return &tree_; }

  virtual void operator()(const VirtualFile&);
  virtual void operator()(const file::VirtualFileList&);
  virtual void mouseDoubleClick(const juce::MouseEvent& e);
  void doAdd();

 private:
  void update();
  void addVolume(const VirtualFile& volume, int insertAt);
  Node* getNode(int i) { return (Node*) root_.getSubItem(i); }
  int getNumNodes() const { return root_.getNumSubItems(); }

  class TreeViewItem : public juce::TreeViewItem {
   public:
    bool mightContainSubItems() { return true; }
  };

  NodeDesc desc_;
  TreeViewItem root_;

  TreeViewDropAll tree_;
  file::VirtualFileList volumes_;

  CriticalSection lock_;
  bool addDialogOpen_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
  JUCE_LEAK_DETECTOR(Root);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
