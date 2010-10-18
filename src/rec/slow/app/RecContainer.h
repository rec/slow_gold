#ifndef __REC_REC_CONTAINER
#define __REC_REC_CONTAINER

#include <algorithm>

#include "rec/gui/RecentFiles.h"
#include "rec/slow/app/ComponentContainer.h"
#include "rec/slow/app/MainPageComponent.h"

namespace rec {

class RecContainer : public ComponentContainer {
 public:
  RecContainer() : mainPage_(new MainPageComponent) {
    show(mainPage_);
  }
  juce_UseDebuggingNewOperator

 private:
  MainPageComponent* mainPage_;
};

}

#endif  // __REC_REC_CONTAINER
