#pragma once

#include <string>

namespace rec {
namespace util {
namespace ews {

extern const char TEST_SERIAL_NUMBER[];

struct Authentication {
  int daysToExpiration;
  std::string user;
  std::string serialNumber;

  bool unauthenticated() const {
    return user.empty() or serialNumber.empty();
  }

  bool expired() const {
    return user.empty() and daysToExpiration <= 0;
  }
};

Authentication testAuthenticated();

std::string confirmAndActivate(
    const std::string& serialNumber,
    const std::string& name);

}  // namespace ews
}  // namespace util
}  // namespace rec
