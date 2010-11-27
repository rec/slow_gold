#ifndef __REC_UTIL_CD_DISCTRACKER__
#define __REC_UTIL_CD_DISCTRACKER__

#include <vector>

#include "rec/base/base.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace util {
namespace cd {

class DiscTracker {
 public:
  DiscTracker(juce::ChangeListener* listener);
  ~DiscTracker();

 private:
  std::vector<juce::AudioCDBurner*> burners_;

  DISALLOW_COPY_AND_ASSIGN(DiscTracker);
};

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_DISCTRACKER__
