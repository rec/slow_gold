#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include <algorithm>

#include "rec/widget/tree/Node.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node {
 public:
  Directory(const NodeDesc& d, const File& f, const File& s) : Node(d, f, s) {}
  virtual bool mightContainSubItems() { return true; }
  virtual void fillSubItems();

 private:
  virtual void fillFewItems();
  virtual void fillManyItems();

  juce::Array<File> children_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
