#if JUCE_WINDOWS

#include <windows.h>

#endif

#include "rec/util/GetEnv.h"

namespace rec {
namespace util {

#define USE_WINDOWS_GETENV 0

inline String getEnv(const char* name, const String& dflt) {
#if USE_WINDOWS_GETENV && JUCE_WINDOWS
  static const int MAX_ENV = 1024;
  char buffer[MAX_ENV];

  if (int len = ::GetEnvironmentVariable(name, buffer, MAX_ENV))
    return str(string(buffer, buffer + len));

#else
  const char* res = getenv(name);
  if (res && *res)
    return String(res);
#endif

  return dflt;
}

}  // namespace util
}  // namespace rec
