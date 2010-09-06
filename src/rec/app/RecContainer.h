#ifndef __REC_REC_CONTAINER
#define __REC_REC_CONTAINER

#include "rec/app/ComponentContainer.h"
#include "rec/components/MainPageComponent.h"

namespace rec {

class RecContainer : public ComponentContainer<RecWindow> {
 public:
  RecContainer(RecWindow* window) : ComponentContainer<RecWindow>(window) {
    show(new MainPageComponent);
  }

  virtual const StringArray getMenuBarNames() {
    static const char* const names[] = {"File", "Edit", NULL};
    return StringArray(names);
  }

  juce_UseDebuggingNewOperator
};

}

#endif  // __REC_REC_CONTAINER
