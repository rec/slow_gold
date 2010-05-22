#ifndef __REC_REC_CONTAINER
#define __REC_REC_CONTAINER

#include "rec/app/ComponentContainer.h"
#include "rec/components/AudioDemoTabComponent.h"

namespace rec {

class RecContainer : public ComponentContainer<RecWindow> {
 public:
  RecContainer(RecWindow* window) : ComponentContainer<RecWindow>(window) {
    show(new AudioDemoTabComponent);
  }

  juce_UseDebuggingNewOperator
};

}

#endif  // __REC_REC_CONTAINER
