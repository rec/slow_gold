#pragma once

#include "rec/base/base.h"

namespace rec {
namespace app {

static const int EXPIRED = 0;
static const int AUTHORIZED = -1;

int daysToExpiration();
bool authenticate(const string& serialNumber);

}  // namespace app
}  // namespace rec
