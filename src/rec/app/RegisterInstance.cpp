#include "rec/app/RegisterInstance.h"
#include "rec/app/Files.h"

namespace rec {
namespace app {

namespace {

const char* const ACCEPTANCE = "SLOWGOLD-SUCCESS";

String getTimestamp() {
  return String(juce::Time::currentTimeMillis());
}

String getVersion() {
  return JUCEApplication::getInstance()->getApplicationVersion();
}

const char* const VARS[] = {
  "USERNAME",
  "USERKEY",
};

const app::RegisterProgram::NamedFunction FUNCS[] = {
  { "timestamp", &getTimestamp },
  { "program", &getApplicationName },
  { "version", &getVersion },
};

const char* const URLS[] = {
  "http://slowgold.com/registration/",
  "http://slowgold.w07.winhost.com/registration/",
};

}  // namespace

RegisterInstance::RegisterInstance() : RegisterProgram("RegisterInstance") {
  setPriority(4);
}

Range<const char* const*> RegisterInstance::getEnvironmentVariables() const {
  return Range<const char* const*>(VARS, VARS + arraysize(VARS));
}

Range<const RegisterInstance::NamedFunction*>
RegisterInstance::getNamedFunctions() const {
  return Range<const NamedFunction*>(FUNCS, FUNCS + arraysize(FUNCS));
}

StringArray RegisterInstance::getBaseUrls() const {
  return StringArray(URLS, arraysize(URLS));
}

String RegisterInstance::resultMatcher() const {
  return ACCEPTANCE;
}


}  // namespace app
}  // namespace rec

