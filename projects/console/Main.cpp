#include <string>
#include <glog/logging.h>

#include "rec/app/GenericApplication.h"

class Main : public rec::GenericApplication {
 public:
  Main() : GenericApplication("main", "0.0") {}
  
  virtual void initialise(const String& commandLineParameters) {
    GenericApplication::initialise(commandLineParameters);
    quit();
  }
};

START_JUCE_APPLICATION(Main)
