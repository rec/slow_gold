#include "glog/logging.h"

#include "rec/util/cd/DiscTracker.h"
#include "rec/base/scoped_ptr.h"
#include "rec/util/STL.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

DiscTracker::DiscTracker(ChangeListener* listener) {
  StringArray burners = AudioCDBurner::findAvailableDevices();
  for (int i = 0; i < burners.size(); ++i) {
    if (AudioCDBurner* burner = AudioCDBurner::openDevice(i)) {
      burners_.push_back(burner);
      burner->addChangeListener(listener);
    } else {
      LOG(ERROR) << "Unable to open burner named " << burners[i].toCString();
    }
  }
}

DiscTracker::~DiscTracker() {
  stl::deletePointers(&burners_);
}

}  // namespace cd
}  // namespace util
}  // namespace rec
