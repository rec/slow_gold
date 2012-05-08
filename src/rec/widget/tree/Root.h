#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/widget/tree/NodeItem.h"

#include "rec/data/DataListener.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/widget/tree/TreeViewDropAll.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public Broadcaster<const VirtualFile&>,
             public data::GlobalDataListener<VirtualFileList>,
             public Listener<const VirtualFile&>,
             public juce::MouseListener {
 public:
  explicit Root(MenuBarModel*,
                const NodeDesc& desc = NodeDesc::default_instance());

  virtual ~Root() {}

  void checkVolumes();
  void mergeNewIntoOld(util::file::VirtualFileList volumes);
  TreeViewDropAll* treeView() { return &tree_; }

  virtual void operator()(const VirtualFile&);
  virtual void operator()(const file::VirtualFileList&);
  virtual void mouseDoubleClick(const juce::MouseEvent& e);
  void readOpenness();

  bool run();  // Update files in a background thread.
  void refreshNode(const VirtualFile&);

 private:
  void update();
  void addVolume(const VirtualFile& volume, int insertAt);
  Node* getNode(int i) { return (Node*) root_.getSubItem(i); }
  int getNumNodes() const { return root_.getNumSubItems(); }
  void writeOpenness();

  class RootNode : public Node {
   public:
    RootNode() : Node(NodeDesc(), VirtualFile()) {}
    virtual bool mightContainSubItems() { return true; }
    virtual String getUniqueName() const { return "root"; }
  };

  NodeDesc desc_;
  RootNode root_;

  TreeViewDropAll tree_;  // This is our actual Component!
  file::VirtualFileList volumes_;

  CriticalSection lock_;
  bool addDialogOpen_;
  bool opennessRead_;
  bool opennessStarted_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Root);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
