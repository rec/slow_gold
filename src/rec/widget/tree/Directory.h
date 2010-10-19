#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include "rec/widget/tree/Node.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node {
 public:
  Directory(const NodeDesc& desc, const Path& path) : Node(desc, path) {
  }
  virtual bool mightContainSubItems() { return true; }
  virtual void fillSubItems() {
    File f = pathToFile(path_);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
