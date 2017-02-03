#pragma once

#include "rec/base/base.h"

namespace rec {
namespace data {

class Address;
struct MessageField;

MessageField createMessageField(const Address&, const Message&);

}  // namespace data
}  // namespace rec
