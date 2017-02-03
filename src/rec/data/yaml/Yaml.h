#pragma once

#include "rec/base/BaseNoJuce.h"

namespace rec {
namespace yaml {

string write(const Message&);
bool read(const string& from, Message* to);

}  // namespace yaml
}  // namespace rec
