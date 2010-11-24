#ifndef __REC_WIDGET_TREE_ROOT__
#define __REC_WIDGET_TREE_ROOT__

#include "rec/base/base.h"
#include "rec/widget/tree/Node.pb.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

class Root : public juce::TreeView {
 public:
  explicit Root(const NodeDesc& desc);
  ~Root();

  void addChildren();

 private:
  void addSubItem(const File& file, const File& shadow);

  NodeDesc desc_;
  scoped_ptr<juce::TreeViewItem> root_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
};


}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
