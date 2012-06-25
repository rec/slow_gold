#ifndef __REC_APP_REGISTERINSTANCE__
#define __REC_APP_REGISTERINSTANCE__

#include "rec/app/RegisterProgram.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace app {

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

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_REGISTERINSTANCE__
