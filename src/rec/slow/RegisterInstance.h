#ifndef __REC_SLOW_REGISTERINSTANCE__
#define __REC_SLOW_REGISTERINSTANCE__

#include "rec/app/RegisterProgram.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace slow {

class RegisterInstance : public app::RegisterProgram {
 public:
  RegisterInstance() : app::RegisterProgram("RegisterInstance") {
    setPriority(4);
  }

  virtual Range<const char**> getEnvironmentVariables() const {
    static const char* VARS[] = {
      "foo",
      "bar",
    };
    return Range<const char**>(VARS, VARS + arraysize(VARS));
  }

  virtual Range<const NamedFunction*> getNamedFunctions() const {
    static const app::RegisterProgram::NamedFunction FUNCTIONS[] = {
      { "baz", NULL },
    };
    return Range<const NamedFunction*>(FUNCTIONS,
                                       FUNCTIONS + arraysize(FUNCTIONS));
  }

  virtual String getBaseUrl() const {
    return "http://slowgold.com/registration";
  }

  virtual int timeOut() const { return 1000; }
  virtual void interpretResult(const String&) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(RegisterInstance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REGISTERINSTANCE__
