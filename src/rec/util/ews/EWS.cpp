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

const char TEST_SERIAL_NUMBER[] =
  "000016-12NGVJ-2VHWCD-QRH6YA-BR1635-0XB5MC-XDX6FV-JCNU3F-E7G3A6-02R2AK";

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

OSStatus confirm(const string& serialNumber) {
  return eWeb_ConfirmSerialNumber(publisherId(), serialNumber.c_str());
}

OSStatus validate(const string& serialNumber) {
  return eWeb_ValidateActivation(
      publisherId(), activationId(), serialNumber.c_str());
}

OSStatus activate(const string& serialNumber) {
  return eWeb_ActivateSerialNumber(
      publisherId(), activationId(), serialNumber.c_str(), false);
}

OSStatus deactivate(const string& serialNumber) {
  return eWeb_DeactivateSerialNumber(
      publisherId(), activationId(), serialNumber.c_str());
}

}  // namespace

Authentication testAuthenticated() {
  Authentication result;
  auto activation = data::getProto<Activation>();
  if (activation.has_samples()) {
    result.serialNumber = crypt(activation.samples());
    auto status = validate(result.serialNumber);
    if (not status) {
      LOG(INFO) << "Sample rate computed.";
      result.user = crypt(activation.frame());
    } else {
      LOG(ERROR) << "No sample rate " << activation.samples() << status;
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

string confirmAndActivate(const string& serialNumber, const string& name) {
  if (confirm(serialNumber))
    return "Invalid serial number";

  if (auto s = activate(serialNumber)) {
    if (s == E_ACTIVATESN_LIMIT_MET)
      return "Too many activations for this key.";
    auto code = String(static_cast<int>(s));
    return ("Unable to activate key, error=" + code).toStdString();
  }

  Activation activation;
  activation.set_samples(crypt(serialNumber));
  activation.set_frame(crypt(name));
  activation.set_rate(fromTime(Time::getCurrentTime()));
  data::setProto(activation);

  return "";
}

}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
