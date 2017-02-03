#pragma once

#include "rec/app/RegisterProgram.h"
#include "rec/app/SocketTimeoutTime.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace app {

class RegisterInstance : public app::RegisterProgram {
  public:
    RegisterInstance();

    virtual Range<const char* const*> getEnvironmentVariables() const;
    virtual Range<const NamedFunction*> getNamedFunctions() const;
    virtual String resultMatcher() const;

    virtual StringArray getBaseUrls() const;

    virtual int timeOut() const { return SOCKET_TIMEOUT_MS; }

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(RegisterInstance);
};

}  // namespace app
}  // namespace rec
