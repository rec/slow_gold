#ifndef __REC_WIDGET_TREE_PARTITIONCHILDREN__
#define __REC_WIDGET_TREE_PARTITIONCHILDREN__

#include "rec/base/base.h"
#include "rec/widget/tree/Range.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

void partitionChildren(const juce::Array<File>&, const Range&, int, juce::Array<int>*);
void partitionChildren(const std::vector<string>&, const Range&, int, std::vector<int>*);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_PARTITIONCHILDREN__
