#pragma once

namespace rec {
namespace util {
namespace ews {

extern const char TEST_SERIAL_NUMBER[];

bool confirm(const char* serialNumber);
bool activate(const char* serialNumber);
bool deactivate(const char* serialNumber);
bool validate(const char* serialNumber);

}  // namespace ews
}  // namespace util
}  // namespace rec
