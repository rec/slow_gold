#pragma once

#include <string>

namespace rec {
namespace util {
namespace ews {

extern const char TEST_SERIAL_NUMBER[];

bool confirm(const std::string& serialNumber);
bool activate(const std::string& serialNumber);
bool deactivate(const std::string& serialNumber);
bool validate(const std::string& serialNumber);

}  // namespace ews
}  // namespace util
}  // namespace rec
