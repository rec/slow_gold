#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/base/base.h"
#include "rec/util/Listener.h"
#include "rec/widget/tree/Node.pb.h"
#include "rec/widget/tree/VolumeFile.pb.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Node;

class Root : public juce::TreeView,
             public util::Listener<const File&>::Set,
             public juce::ChangeListener {
 public:
  explicit Root(const NodeDesc& desc);
  ~Root();

  void update();
  virtual void changeListenerCallback(void*) { update(); }

 private:
  void addVolume(const VolumeFile& volumeFile);
  void addVolume(Volume::Type type, const string& name);

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
