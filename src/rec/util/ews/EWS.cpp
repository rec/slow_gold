#ifdef __APPLE__

#include <glog/logging.h>

#include "ews/EWSEmbedded.h"
#include "rec/util/ews/EWS.h"

namespace rec {
namespace util {
namespace ews {

namespace {

const char PUBLISHER_ID[] = "PUB4876107970";
const char ACTIVATION_ID[] =
  "ACT3511648730:L3L2KT-HQLC-DH8NEY-UUHL-V1935A-5GXW22-XL4E-VHNAPV-J7ZY-A3EQPH";
const char OK[] = "";
const char FAILED[] = "failed";

bool isSystemCompatible() {
  return eWeb_IsSystemCompatible();
}

}

const char TEST_SERIAL_NUMBER[] =
  "000016-12NGVJ-2VHWCD-QRH6YA-BR1635-0XB5MC-XDX6FV-JCNU3F-E7G3A6-02R2AK";

bool confirm(const char* serialNumber) {
  auto status = eWeb_ConfirmSerialNumber(PUBLISHER_ID, serialNumber);
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << PUBLISHER_ID
               << ", " << serialNumber;
  }
  return not status;
}

bool activate(const char* serialNumber) {
  auto status = eWeb_ActivateSerialNumber(
      PUBLISHER_ID, ACTIVATION_ID, serialNumber, false);
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << PUBLISHER_ID
               << ", " << ACTIVATION_ID
               << ", " << serialNumber;
  }
  return not status;
}

bool deactivate(const char* serialNumber) {
  auto status = eWeb_DeactivateSerialNumber(
      PUBLISHER_ID, ACTIVATION_ID, serialNumber);
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << PUBLISHER_ID
               << ", " << ACTIVATION_ID
               << ", " << serialNumber;
  }
  return not status;
}

bool validate(const char* serialNumber) {
  auto status = eWeb_ValidateActivation(
      PUBLISHER_ID, ACTIVATION_ID, serialNumber);
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << PUBLISHER_ID
               << ", " << ACTIVATION_ID
               << ", " << serialNumber;
  }
  return not status;
}

}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
