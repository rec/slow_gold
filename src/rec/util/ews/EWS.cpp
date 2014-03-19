#ifdef __APPLE__

#include <glog/logging.h>

#include "ews/EWSEmbedded.h"
#include "rec/util/ews/EWS.h"

namespace rec {
namespace util {
namespace ews {

namespace {

const char PUBLISHER_ID[] = "STR6720703889";
const char ACTIVATION_ID[] = "ACT3511648730:L3L2KT-HQLC-DH8NEY-UUHL-V1935A-5GXW22-XL4E-VHNAPV-J7ZY-A3EQPH";
const char OK[] = "";
const char FAILED[] = "failed";

bool isSystemCompatible() {
  return eWeb_IsSystemCompatible();
}

}

const char TEST_SERIAL_NUMBER[] = "000016-12VGVJ-2VHXN9-FJRTTZ-FQG6AD-XZ1JPW-ATWBFY-HV9NTJ-JXJU65-7T5E7M";

bool confirm(const char* serialNumber) {
  auto status = eWeb_ConfirmSerialNumber(PUBLISHER_ID, serialNumber);
  if (status)
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status;
  return not status;
}

bool activate(const char* serialNumber) {
  auto status = eWeb_ActivateSerialNumber(
      PUBLISHER_ID, ACTIVATION_ID, serialNumber, false);
  if (status)
    LOG(ERROR) << "eWeb_ActivateSerialNumber: " << status;
  return not status;
}

bool deactivate(const char* serialNumber) {
  auto status = eWeb_DeactivateSerialNumber(
      PUBLISHER_ID, ACTIVATION_ID, serialNumber);
  if (status)
    LOG(ERROR) << "eWeb_DeactivateSerialNumber: " << status;
  return not status;
}

bool validate(const char* serialNumber) {
  auto status = eWeb_ValidateActivation(
      PUBLISHER_ID, ACTIVATION_ID, serialNumber);
  if (status)
    LOG(ERROR) << "eWeb_ValidateActivation: " << status;
  return not status;
}

}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
