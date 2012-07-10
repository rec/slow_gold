#include <map>

#include "rec/app/RegisterProgram.h"

namespace rec {
namespace app {

namespace {

const bool USE_POSTDATA = false;
const char* const EMPTY_PARAMETER = "NONE";

#define USE_WINDOWS_GETENV 1

inline String getEnv(const char* name, const String& dflt) {
#if USE_WINDOWS_GETENV && JUCE_WINDOWS
  static const int MAX_ENV = 1024;
  char buffer[MAX_ENV];

  if (int len = GetEnvironmentVariable(name, buffer, MAX_ENV))
    return str(string(buffer, buffer + len));

#else
  const char* res = getenv(name);
  if (res && *res)
    return String(res);
#endif

  return dflt;
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

  LOG(ERROR) << "Failed to register any URLs.";
}

bool RegisterProgram::tryOneUrl(const String& urlName) {
  URL url(urlName);
  Range<const char* const*> r = getEnvironmentVariables();
  for (const char* const* i = r.begin_; i != r.end_; ++i)
    url = url.withParameter(*i, getEnv(*i, EMPTY_PARAMETER));

  Range<const NamedFunction*> s = getNamedFunctions();
  for (const NamedFunction* i = s.begin_; i != s.end_; ++i)
    url = url.withParameter(i->name_, i->function_());
  ptr<InputStream> stream(url.createInputStream(USE_POSTDATA,
                                                progressCallback(),
                                                this, "", timeOut(),
                                                NULL));
  if (!stream)
    LOG(ERROR) << "Couldn't create input stream for URL " << url.toString(true);
  else if (acceptResult(stream->readEntireStreamAsString()))
    return true;
  else
    LOG(ERROR) << "Didn't accept result for URL " << url.toString(true);

  return false;
}

bool RegisterProgram::acceptResult(const String& result) const {
  return result.contains(resultMatcher());
}

}  // namespace app
}  // namespace rec
