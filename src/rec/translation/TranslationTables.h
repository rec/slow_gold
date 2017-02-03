#pragma once

#include "rec/base/Trans.h"
#include "rec/util/Listener.h"

namespace rec {
namespace translation {

string translate(const TranslatedString& translation);
Language getLanguage();

}  // namespace translation
}  // namespace rec

