#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#if 0
#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public juce::TreeView {
 public:
  explicit Root(const NodeDesc& desc) : desc_(desc) {}
  ~Root();

  void addChildren();

 private:
  void addSubItem(const File& file, const File& shadow)

  NodeDesc desc_;
  TreeViewItem root_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
};


}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif 

#endif  // __REC_WIDGET_TREE_ROOT__
