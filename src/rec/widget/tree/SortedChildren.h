#ifndef __REC_WIDGET_TREE_SORTEDCHILDREN__
#define __REC_WIDGET_TREE_SORTEDCHILDREN__

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

void sortedChildren(const File& f, juce::Array<File>* files,
                    const juce::Thread* threadToCheck = NULL);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_SORTEDCHILDREN__
