#include "rec/widget/tree/Tree.h"
#include "rec/util/partition/PartitionChildren.h"

namespace rec {
namespace widget {
namespace tree {

void eraseVolumePrefix(string* name, bool diskToo) {
  static const int len = strlen("/Volumes/");
  if (name->find("/Volumes/") == 0) {
    int pos = diskToo ? name->find("/", len) : len;
    if (pos != -1)
      name->erase(0, pos);
  }
}

bool compareFiles(const File& f, const File& g) {
  return partition::compareStrings(f.getFileName(), g.getFileName()) < 0;
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
