#include "rec/app/AppDirectory.h"

namespace rec {
namespace app {

namespace {

String applicationName;
const char COMPANY_NAME[] = "World Wide Woodshed";

}  // namespace

void setName(const String& name) {
  CHECK(!applicationName.length());
  applicationName = name;
}

const String& getName() { return applicationName; }

File getDirectory() {
  return File::getSpecialLocation(File::userApplicationDataDirectory).
    getChildFile(COMPANY_NAME).
     getChildFile(applicationName);
}

}  // namespace app
}  // namespace rec

