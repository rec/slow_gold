#include <map>

#include "rec/app/RegisterProgram.h"

namespace rec {
namespace app {

namespace {

inline String getEnv(const char* name) {
#if 0 && JUCE_WINDOWS
  static const int MAX_ENV = 1024;
  char buffer[MAX_ENV];

  int len = GetEnvironmentVariable(name, buffer, MAX_ENV);
  return str(string(buffer, buffer + len));

#else
  const char* res = getenv(name);
  return String(res ? res : "");
#endif
}

}  // namespace

void RegisterProgram::run() {
  typedef std::map<String, String> StringMap;

  URL url(getBaseUrl());
  Range<const char**> r = getEnvironmentVariables();
  for (const char** i = r.begin_; i != r.end_; ++i)
    url = url.withParameter(*i, getenv(*i));

  Range<const NamedFunction*> s = getNamedFunctions();
  for (const NamedFunction* i = s.begin_; i != s.end_; ++i)
    url = url.withParameter(i->name_, i->function_());
  ptr<InputStream> stream(url.createInputStream(true, progressCallback(),
                                                this, "", timeOut(),
                                                NULL));
  if (acceptResult(stream->readEntireStreamAsString()))
    onSuccess();
  else
    LOG(ERROR) << "Failed to register";
}

bool RegisterProgram::acceptResult(const String& result) const {
  return !result.contains("404");  // HACK!
}

}  // namespace app
}  // namespace rec
