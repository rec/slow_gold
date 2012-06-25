#ifndef __REC_APP_REGISTERPROGRAM__
#define __REC_APP_REGISTERPROGRAM__

#include "rec/util/Range.h"

namespace rec {
namespace app {

class RegisterProgram : public Thread {
 public:
  struct NamedFunction {
    typedef String (*StringFunction)();

    const char* name_;
    StringFunction function_;
  };

  RegisterProgram(const String& name) : Thread(name) {}
  virtual ~RegisterProgram() {}

  virtual Range<const char**> getEnvironmentVariables() const = 0;
  virtual Range<const NamedFunction*> getNamedFunctions() const = 0;
  virtual String getBaseUrl() const = 0;
  virtual bool acceptResult(const String&) const = 0;
  virtual void interpretResult(const String&) = 0;
  virtual int timeOut() const = 0;
  virtual URL::OpenStreamProgressCallback* progressCallback() const {
    return NULL;
  }

  virtual void run() {
    URL url(getBaseUrl());
    Range<const char**> r = getEnvironmentVariables();
    for (const char** i = r.begin_; i != r.end_; ++i)
      url = url.withParameter(*i, getenv(*i));

    Range<const NamedFunction*> s = getNamedFunctions();
    for (const NamedFunction* i = s.begin_; i != s.end_; ++i)
      url = url.withParameter(i->name_, i->function_());
    ptr<InputStream> stream(url.createInputStream(true, progressCallback(),
                                                  this, "", timeOut()));
    interpretResult(stream->readEntireStreamAsString());
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(RegisterProgram);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_REGISTERPROGRAM__
