#ifndef __REC_WIDGET_TREE_CDREADER__
#define __REC_WIDGET_TREE_CDREADER__

#include "rec/base/base.h"

namespace juce {
  
class AudioCDReader;

}

namespace rec {
namespace widget {
namespace tree {

juce::AudioCDReader* getCDReader(const string& idString);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_CDREADER__
