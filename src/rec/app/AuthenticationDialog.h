#pragma once

#include "rec/base/base.h"

namespace rec {
namespace app {

struct Authentication {
  int daysToExpiration;
  string user;
  string serialNumber;
};

Authentication testAuthenticated();
bool authenticate(const string& serialNumber);

}  // namespace app
}  // namespace rec
