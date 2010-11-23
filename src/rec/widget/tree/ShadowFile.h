#ifndef __REC_WIDGET_TREE_SHADOWFILE__
#define __REC_WIDGET_TREE_SHADOWFILE__

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

struct ShadowFile {
  File file_;
  File shadow_;

  ShadowFile() {}
  ShadowFile(const File& f, const File& s) : file_(f), shadow_(s) {}
};


}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_SHADOWFILE__
