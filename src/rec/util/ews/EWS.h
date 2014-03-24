#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace ews {

struct Authentication {
  int daysToExpiration;
  string user;
  string serialNumber;
  bool authenticatedCouldntConnect;

  bool unauthenticated() const {
    return user.empty();
  }

  bool expired() const {
    return user.empty() and daysToExpiration <= 0;
  }
};

Authentication testAuthenticated();

string confirmAndActivate(const string& serialNumber, const string& name);

}  // namespace ews
}  // namespace util
}  // namespace rec
