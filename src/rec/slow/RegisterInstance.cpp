#include "rec/slow/RegisterInstance.h"

namespace rec {
namespace slow {

namespace {

String getTimestamp() {
  return String(juce::Time::currentTimeMillis());
}

const app::RegisterProgram::NamedFunction FUNCS[] = {
  { "timestamp", &getTimestamp },
};

const char* VARS[] = {
  "foo",
  "bar",
};

}

RegisterInstance::RegisterInstance() : app::RegisterProgram("RegisterInstance") {
  setPriority(4);
}

Range<const char**> RegisterInstance::getEnvironmentVariables() const {
  return Range<const char**>(VARS, VARS + arraysize(VARS));
}

bool RegisterInstance::acceptResult(const String& s) const {
  return true;
}

Range<const RegisterInstance::NamedFunction*>
RegisterInstance::getNamedFunctions() const {
  return Range<const NamedFunction*>(FUNCS, FUNCS + arraysize(FUNCS));
}

String RegisterInstance::getBaseUrl() const {
  return "http://slowgold.com/registration";
}

void RegisterInstance::interpretResult(const String&) {
}

}  // namespace slow
}  // namespace rec
