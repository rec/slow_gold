#include <map>

#include "rec/app/RegisterProgram.h"
#include "rec/util/GetEnv.h"

namespace rec {
namespace app {

namespace {

const bool USE_POSTDATA = false;
//const char* const EMPTY_PARAMETER = "NONE";

}  // namespace

void RegisterProgram::run() {
  StringArray urls = getBaseUrls();
  for (int i = 0; i < urls.size(); ++i) {
    const String& url(urls[i]);
    if (tryOneUrl(url)) {
      onSuccess();
      LOG(INFO) << "Registered the program at " << str(url);
      return;
    }
  }

#ifndef DEBUG
  LOG(ERROR) << "Failed to register any URLs from list "
             << str(urls.joinIntoString(", "));
#endif
}

bool RegisterProgram::tryOneUrl(const String& urlName) {
  URL url(urlName);
  Range<const char* const*> r = getEnvironmentVariables();
  for (const char* const* i = r.begin_; i != r.end_; ++i)
    url = url.withParameter(*i, getEnv(*i));

  Range<const NamedFunction*> s = getNamedFunctions();
  for (const NamedFunction* i = s.begin_; i != s.end_; ++i)
    url = url.withParameter(i->name_, i->function_());
  ptr<InputStream> stream(url.createInputStream(USE_POSTDATA,
                                                progressCallback(),
                                                this, "", timeOut(),
                                                nullptr));
  if (!stream) {
    LOG(ERROR) << "Couldn't create input stream for URL " << url.toString(true);
    return false;
  }
  String result = stream->readEntireStreamAsString();
  if (acceptResult(result))
    return true;

#ifndef DEBUG
  LOG(ERROR) << "Didn't accept result for URL " << url.toString(true);
  LOG(ERROR) << "Result: \n " << str(result);
#endif

  return false;
}

bool RegisterProgram::acceptResult(const String& result) const {
  return result.contains(resultMatcher());
}

}  // namespace app
}  // namespace rec
