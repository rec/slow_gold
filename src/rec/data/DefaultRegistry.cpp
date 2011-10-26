#include "rec/data/DefaultRegistry.h"

namespace rec {
namespace data {

void DefaultRegistry::registerDefault(const Message& message) {
}

void DefaultRegistry::registerAddress(const Message&, const Address& address) {
}

Message* DefaultRegistry::getDefault(const string& typeName, const Address& address) {
  return NULL;
}

}  // namespace data
}  // namespace rec
