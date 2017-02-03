#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

extern const char* const EMPTY_ENV_VARIABLE;
String getEnv(const String& name, const String& dflt = EMPTY_ENV_VARIABLE);

}  // namespace util
}  // namespace rec

