#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace app {

class RegisterProgram : public Thread {
  public:
    struct NamedFunction {
        using StringFunction = String (*)();

        const char* name_;
        StringFunction function_;
    };

    explicit RegisterProgram(const String& name) : Thread(name) {}

    virtual ~RegisterProgram() {}

    virtual Range<const char* const*> getEnvironmentVariables() const = 0;
    virtual Range<const NamedFunction*> getNamedFunctions() const = 0;
    virtual StringArray getBaseUrls() const = 0;
    virtual bool acceptResult(const String&) const;
    virtual String resultMatcher() const = 0;
    virtual void onSuccess() {}
    virtual int timeOut() const = 0;
    virtual URL::OpenStreamProgressCallback* progressCallback() const {
        return nullptr;
    }

    virtual void run();

  private:
    bool tryOneUrl(const String&);

    DISALLOW_COPY_ASSIGN_AND_LEAKS(RegisterProgram);
};

}  // namespace app
}  // namespace rec
