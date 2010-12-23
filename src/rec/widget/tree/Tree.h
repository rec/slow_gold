#ifndef __REC_WIDGET_TREE_TREE__
#define __REC_WIDGET_TREE_TREE__

#include "rec/util/Range.h"

namespace rec {
namespace widget {
namespace tree {

void eraseVolumePrefix(string* name, bool diskToo = true);
bool compareFiles(const File& f, const File& g);


}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREE__
