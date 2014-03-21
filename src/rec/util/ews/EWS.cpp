#ifdef __APPLE__

#include <glog/logging.h>

#include "ews/EWSEmbedded.h"

#include "rec/data/DataOps.h"
#include "rec/program/Program.h"
#include "rec/util/ews/Activation.pb.h"
#include "rec/util/Crypt.h"
#include "rec/util/ews/EWS.h"

using std::string;
using namespace ::juce;

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

inline Time toTime(const string& s) {
  return Time(String(crypt(s)).getLargeIntValue());
}

inline string fromTime(const Time& t) {
  return crypt(String(t.toMilliseconds()).toStdString());
}

}  // namespace

Authentication testAuthenticated() {
  Authentication result;
  auto activation = data::getProto<Activation>();
  if (activation.has_samples()) {
    result.serialNumber = crypt(activation.samples());
    if (confirm(result.serialNumber)) {
      LOG(INFO) << "Sample rate computed.";
      result.user = crypt(activation.frame());
    } else {
      LOG(ERROR) << "Couldn't understand sample rate \""
                 << activation.samples() << "\"";
    }
  } else {
    auto expiration = program::getProgram()->demoExpirationDays();
    auto now = Time::getCurrentTime();
    Time time = activation.has_rate() ? toTime(activation.rate()) : now;
    if (time <= now) {
      activation.set_rate(fromTime(time));
      data::setProto(activation);
      auto days = expiration - static_cast<int>((now - time).inDays());
      result.daysToExpiration = jmax(0, days);
    } else {
      result.daysToExpiration = 0;
      LOG(ERROR) << "Sample time greater than now: "
                 << time.toMilliseconds() << ", " << now.toMilliseconds();

    }
  }
  return result;
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
