#ifdef __APPLE__

#include <glog/logging.h>

#include "ews/EWSEmbedded.h"
#include "rec/util/ews/EWS.h"
#include "rec/program/Program.h"

using std::string;

namespace rec {
namespace util {
namespace ews {

namespace {

bool isSystemCompatible() {
  return eWeb_IsSystemCompatible();
}

const char* publisherId() {
  return program::getProgram()->getPublisherId();
}

const char* activationId() {
  return program::getProgram()->getPublisherId();
}

}

const char TEST_SERIAL_NUMBER[] =
  "000016-12NGVJ-2VHWCD-QRH6YA-BR1635-0XB5MC-XDX6FV-JCNU3F-E7G3A6-02R2AK";

bool confirm(const string& serialNumber) {
  auto status = eWeb_ConfirmSerialNumber(publisherId(), serialNumber.c_str());
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << publisherId()
               << ", " << serialNumber;
  }
  return not status;
}

bool activate(const string& serialNumber) {
  auto status = eWeb_ActivateSerialNumber(
      publisherId(), activationId(), serialNumber.c_str(), false);
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << publisherId()
               << ", " << activationId()
               << ", " << serialNumber;
  }
  return not status;
}

bool deactivate(const string& serialNumber) {
  auto status = eWeb_DeactivateSerialNumber(
      publisherId(), activationId(), serialNumber.c_str());
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << publisherId()
               << ", " << activationId()
               << ", " << serialNumber;
  }
  return not status;
}

bool validate(const string& serialNumber) {
  auto status = eWeb_ValidateActivation(
      publisherId(), activationId(), serialNumber.c_str());
  if (status) {
    LOG(ERROR) << "eWeb_ConfirmSerialNumber: " << status
               << ", " << publisherId()
               << ", " << activationId()
               << ", " << serialNumber;
  }
  return not status;
}

}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
