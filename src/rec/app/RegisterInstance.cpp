#include "rec/app/RegisterInstance.h"
#include "rec/app/Files.h"

namespace rec {
namespace app {

namespace {

String getTimestamp() {
  return String(juce::Time::currentTimeMillis());
}

String getVersion() {
  return JUCEApplication::getInstance()->getApplicationVersion();
}

const app::RegisterProgram::NamedFunction FUNCS[] = {
  { "timestamp", &getTimestamp },
  { "program", &getApplicationName },
  { "version", &getVersion },
};

const char* VARS[] = {
  "USERNAME",
  "USERKEY",
};

}  // namespace

RegisterInstance::RegisterInstance() : RegisterProgram("RegisterInstance") {
  setPriority(4);
}

Range<const char**> RegisterInstance::getEnvironmentVariables() const {
  return Range<const char**>(VARS, VARS + arraysize(VARS));
}

Range<const RegisterInstance::NamedFunction*>
RegisterInstance::getNamedFunctions() const {
  return Range<const NamedFunction*>(FUNCS, FUNCS + arraysize(FUNCS));
}

String RegisterInstance::getBaseUrl() const {
  return "http://slowgold.com/registration";
}

}  // namespace app
}  // namespace rec

