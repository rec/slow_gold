#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

class HasLock {
  public:
    HasLock() {}
    const CriticalSection& lock() const { return lock_; }

  protected:
    CriticalSection lock_;

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(HasLock);
};

}  // namespace util
}  // namespace rec
