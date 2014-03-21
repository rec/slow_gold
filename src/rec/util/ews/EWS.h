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

bool confirm(const std::string& serialNumber);
bool activate(const std::string& serialNumber);
bool deactivate(const std::string& serialNumber);
bool validate(const std::string& serialNumber);

}  // namespace ews
}  // namespace util
}  // namespace rec
