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

class Root : public juce::TreeView,
             public util::Listener<const File&>::Set {
 public:
  explicit Root(const NodeDesc& desc);
  ~Root();

  void addChildren();

 private:
  void addSubItem(const VolumeFile& volumeFile);

  NodeDesc desc_;
  scoped_ptr<juce::TreeViewItem> root_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Root);
};


}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_ROOT__
