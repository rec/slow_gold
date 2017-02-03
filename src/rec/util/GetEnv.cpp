#include "rec/util/GetEnv.h"

namespace rec {
namespace util {

const char* const EMPTY_ENV_VARIABLE = "NONE";
String getEnv(const String& name, const String& dflt) {
    return juce::SystemStats::getEnvironmentVariable(name, dflt);
}

}  // namespace util
}  // namespace rec
