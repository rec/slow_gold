#pragma once

#include "rec/base/base.h"

namespace rec {
namespace app {

struct Authentication {
  int daysToExpiration;
  string user;
  string serialNumber;

  bool unauthenticated() const {
    return user.empty() or serialNumber.empty();
  }

  bool expired() const {
    return user.empty() and daysToExpiration <= 0;
  }
};

Authentication testAuthenticated();
bool authenticate(const string& serialNumber);

}  // namespace app
}  // namespace rec
