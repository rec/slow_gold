#include "rec/app/Files.h"

namespace rec {
namespace app {

namespace {

String applicationName;
const char COMPANY_NAME[] = "World Wide Woodshed";

}  // namespace

void setName(const String& name) {
  DCHECK(!applicationName.length());
  applicationName = name;
}

const String& getName() { return applicationName; }

File getAppDirectory() {
  return File::getSpecialLocation(File::userApplicationDataDirectory).
    getChildFile(COMPANY_NAME).
     getChildFile(applicationName);
}

File getAppFile(const String& name) {
  return getAppDirectory().getChildFile(name);
}

}  // namespace app
}  // namespace rec

