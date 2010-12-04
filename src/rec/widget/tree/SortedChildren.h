#ifndef __REC_WIDGET_TREE_SORTEDCHILDREN__
#define __REC_WIDGET_TREE_SORTEDCHILDREN__

#include "rec/base/base.h"

namespace rec {
namespace widget {
namespace tree {

bool isHiddenFile(const File& file);
bool isAudioFileOrDirectory(const File& file);

typedef bool FileFilter(const File& file);

void sortedChildren(const File& f, juce::Array<File>* files,
                    FileFilter* filter = &isAudioFileOrDirectory);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_SORTEDCHILDREN__
