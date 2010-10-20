#include <glog/logging.h>
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/SortedChildren.h"

namespace rec {
namespace widget {
namespace tree {

void Directory::fillFewItems() {
  for (int i = 0; i < children_.size(); ++i) {
    File f = children_[i];
    File s = shadow_.getChildFile(f.getFileName());
    bool isDir = f.isDirectory();
    addSubItem(isDir ? new Directory(desc_, f, s) : new Node(desc_, f, s));
  }
}

void Directory::fillManyItems() {
}

void Directory::fillSubItems() {
  if (!file_.exists()) {
    LOG(ERROR) << file_.getFullPathName().toCString() << " doesn't exist";
    return;
  }
  if (!file_.isDirectory()) {
    LOG(ERROR) << file_.getFullPathName().toCString() << " is not a directory";
    return;
  }

  sortedChildren(file_, &children_);
  if (children_.size() <= desc_.max_branch())
    fillFewItems();
  else
    fillManyItems();
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
