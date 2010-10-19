#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include "rec/widget/tree/Node.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node {
 public:
  Directory(const NodeDesc& desc, const Address& addr) : Node(desc, addr) {}
  virtual bool mightContainSubItems() { return true; }



 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
