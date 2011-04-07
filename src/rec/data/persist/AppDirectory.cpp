#include "rec/data/persist/AppDirectory.h"

namespace rec {
namespace util {

namespace {

String applicationName;
const char COMPANY_NAME[] = "World Wide Woodshed";

}  // namespace

void setApplicationName(const String& name) {
  CHECK(!applicationName.length());
  LOG(INFO) << "Application name: " << name;
  applicationName = name;
}

const String& getApplicationName() { return applicationName; }

File getApplicationDirectory() {
  return File::getSpecialLocation(File::userApplicationDataDirectory).
    getChildFile(COMPANY_NAME).
     getChildFile(applicationName);
}

}  // namespace util
}  // namespace rec
