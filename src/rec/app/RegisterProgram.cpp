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
  StringArray urls = getBaseUrls();
  for (int i = 0; i < urls.size(); ++i) {
    if (tryOneUrl(urls[i])) {
      onSuccess();
      return;
    }
  }

  LOG(ERROR) << "Failed to register URLs: " << urls.joinIntoString(", ");
}

bool RegisterProgram::tryOneUrl(const String& urlName) {
  URL url(urlName);
  Range<const char* const*> r = getEnvironmentVariables();
  for (const char* const* i = r.begin_; i != r.end_; ++i)
    url = url.withParameter(*i, getenv(*i));

  Range<const NamedFunction*> s = getNamedFunctions();
  for (const NamedFunction* i = s.begin_; i != s.end_; ++i)
    url = url.withParameter(i->name_, i->function_());
  ptr<InputStream> stream(url.createInputStream(true, progressCallback(),
                                                this, "", timeOut(),
                                                NULL));
  return stream && acceptResult(stream->readEntireStreamAsString());
}

bool RegisterProgram::acceptResult(const String& result) const {
  return !result.contains("404");  // HACK!
}

}  // namespace app
}  // namespace rec
