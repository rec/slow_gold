#include <map>

#include "rec/app/RegisterProgram.h"

namespace rec {
namespace app {

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
