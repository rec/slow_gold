#ifndef __REC_WIDGET_TREE_PARTITIONCHILDREN__
#define __REC_WIDGET_TREE_PARTITIONCHILDREN__

#include "rec/base/base.h"
#include "rec/widget/tree/Range.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

void partitionChildren(const juce::Array<File>& kids, const Range& range,
                       int branching, juce::Array<int>* partition);

void partitionChildren(const std::vector<string>& kids, const Range& range,
                       int branching, std::vector<int>* partition);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_PARTITIONCHILDREN__
