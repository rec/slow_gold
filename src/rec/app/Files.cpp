#include "rec/app/Files.h"

namespace rec {
namespace app {

namespace {

String applicationName;
const char COMPANY_NAME[] = "World Wide Woodshed";

}  // namespace

void setApplicationName(const String& name) {
  DCHECK(!applicationName.length());
  applicationName = name;
}

File getCompanyDirectory() {
  return File::getSpecialLocation(File::userApplicationDataDirectory).
    getChildFile(COMPANY_NAME);
}

File getAppDirectory() {
  return getCompanyDirectory().getChildFile(applicationName);
}

File getAppFile(const String& name) {
  return getAppDirectory().getChildFile(name);
}

}  // namespace app
}  // namespace rec

