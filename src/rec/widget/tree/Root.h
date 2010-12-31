#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/widget/tree/NodeItem.h"
#include "rec/util/file/VolumeFile.pb.h"
#include "rec/util/file/GetVolumes.h"
#include "rec/util/listener/DataListener.h"
#include "rec/widget/tree/TreeViewDropAll.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public Thread,
             public Broadcaster<const VolumeFile&>,
             public Listener<const file::VolumeFileList&>,
             public Listener<const VolumeFile&> {
 public:
  explicit Root(const NodeDesc& desc);
  virtual ~Root() {}

  virtual void run();
  void mergeNewIntoOld(const util::file::VolumeFileList& volumes);
  TreeView* treeView() { return &tree_; }

  virtual void operator()(const VolumeFile&);
  virtual void operator()(const file::VolumeFileList&);

 private:
  void update();
  void addVolume(const VolumeFile& volume, int insertAt);
  Node* getNode(int i) { return (Node*) root_.getSubItem(i); }
  int getNumNodes() const { return root_.getNumSubItems(); }

  class TreeViewItem : public juce::TreeViewItem {
   public:
    bool mightContainSubItems() { return true; }
  };

  NodeDesc desc_;
  TreeViewItem root_;

  TreeViewDropAll tree_;
  file::VolumeFileList volumes_;

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
  JUCE_LEAK_DETECTOR(Root);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
