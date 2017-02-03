#pragma once

#include "rec/base/base.h"

// A class with only a virtual destructor.

namespace rec {
namespace util {

class Deletable {
  public:
    Deletable() {}
    virtual ~Deletable() {}

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(Deletable);
};

}  // namespace util
}  // namespace rec
