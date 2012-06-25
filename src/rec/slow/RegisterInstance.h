#ifndef __REC_SLOW_REGISTERINSTANCE__
#define __REC_SLOW_REGISTERINSTANCE__

#include "rec/app/RegisterProgram.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace slow {

class RegisterInstance : public app::RegisterProgram {
 public:
  RegisterInstance();

  virtual Range<const char**> getEnvironmentVariables() const;

  virtual Range<const NamedFunction*> getNamedFunctions() const;

  virtual String getBaseUrl() const;
  virtual bool acceptResult(const String&) const;
  virtual void interpretResult(const String&);

  static const int TIME_OUT = 1000;

  virtual int timeOut() const { return TIME_OUT; }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(RegisterInstance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REGISTERINSTANCE__
