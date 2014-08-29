#ifdef __APPLE__

#include "ews/EWSEmbedded.h"

#include "rec/util/ews/EWS.h"
#include "rec/base/Trans.h"
#include "rec/data/DataOps.h"
#include "rec/data/Opener.h"
#include "rec/program/Program.h"
#include "rec/util/ews/Activation.pb.h"
#include "rec/util/Crypt.h"

#define EWS_AUTHENTICATION

using std::string;
using namespace ::juce;

TRAN(INVALID_SERIAL_NUMBER, "Invalid serial number");
TRAN(TOO_MANY_ACTIVATIONS, "Too many activations for this key.");
TRAN(UNABLE_TO_ACTIVATE, "Unable to activate key, error=");
TRAN(NETWORK_ISSUES, "Network connection issue.  Please try again later.");
TRAN(UNKNOWN_ERROR, "Unknown error - please report to technical support. "
     "Code=");

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
  return program::getProgram()->getActivationId();
}

inline Time toTime(const string& s) {
  return Time(String(crypt(s)).getLargeIntValue());
}

inline string fromTime(const Time& t) {
  return crypt(String(t.toMilliseconds()).toStdString());
}

inline Time daysAfterNow(int days) {
  return Time::getCurrentTime() + RelativeTime::days(days);
}

inline string fromTime(const RelativeTime& t) {
  return fromTime(Time::getCurrentTime() + t);
}

inline string fromTimeDays(int days) {
  return fromTime(daysAfterNow(days));
}

OSStatus confirm(const string& serialNumber) {
  return eWeb_ConfirmSerialNumber(publisherId(), serialNumber.c_str());
}

OSStatus activate(const string& serialNumber) {
  return eWeb_ActivateSerialNumber(
      publisherId(), activationId(), serialNumber.c_str(), false);
}

bool validate(const string& serialNumber) {
  auto status = eWeb_ValidateActivation(
      publisherId(), activationId(), serialNumber.c_str());
  if (status == E_VALIDATEACTIVATION_MACHINE_MATCH)
    return true;

  if (status != E_INET_CONNECTION_FAILURE and
      status != E_INET_ESELLERATE_FAILURE) {
    return false;
  }

  if (serialNumber.size() != strlen(TEST_SERIAL_NUMBER))
    return false;

  for (auto i = 0; i < serialNumber.size(); ++i) {
    auto ch = serialNumber[i];
    if ((i + 1) % 6) {
      if (not (isdigit(ch) or isupper(ch)))
        return false;
      if (ch == 'I' or ch == 'O' or ch == 'V' or ch == 'Z')
        return false;
    } else if (ch != '-') {
      return false;
    }
  }

  return true;
}

}  // namespace

Authentication testAuthenticated() {
  Authentication result;
#ifdef EWS_AUTHENTICATION
  auto activation = data::getProto<Activation>();

  if (activation.has_samples()) {
    result.serialNumber = crypt(activation.samples());
    if (validate(result.serialNumber))
      result.user = crypt(activation.frame());
  } else {
    auto daysToExpiration = program::getProgram()->demoExpirationDays();
    if (activation.has_rate()) {
      auto time = toTime(activation.rate());
      auto now = Time::getCurrentTime();
      auto days = std::max(static_cast<int>((time - now).inDays()), 0);
      if (days > daysToExpiration) {
        result.daysToExpiration = 0;
        LOG(ERROR) << "Sample time greater than now: "
                   << time.toMilliseconds() << ", " << now.toMilliseconds();
      } else {
        result.daysToExpiration = days;
      }
    } else {
      result.daysToExpiration = daysToExpiration;
      activation.set_rate(fromTimeDays(daysToExpiration));
    }
  }
#else
  result.user = "Tempo Rary";
#endif
  return result;
}

String deactivate(const string& serialNumber) {
#ifdef EWS_AUTHENTICATION
  if (auto status = eWeb_DeactivateSerialNumber(
          publisherId(), activationId(), serialNumber.c_str())) {
    if (status <= E_DEACTIVATION_NO_SUCH_SERIAL_NUMBER and
        status >= E_DEACTIVATION_DEACTIVATION_LIMIT_MET) {
      return t_INVALID_SERIAL_NUMBER;
    }

    if (status <= E_INET_CONNECTION_FAILURE and
        status >= E_INET_ESTATE_NOT_FOUND) {
      return t_NETWORK_ISSUES;
    }

    return t_UNKNOWN_ERROR + String(static_cast<int>(status));
  }

  data::Opener<Activation> activation(data::CANT_UNDO);
  activation->clear_samples();
  auto days = program::getProgram()->unauthorizedExpirationDays();
  activation->set_rate(fromTimeDays(days));
  activation->clear_frame();
#endif

  return "";
}

string confirmAndActivate(const string& serialNumber, const string& name) {
#ifdef EWS_AUTHENTICATION
  if (confirm(serialNumber))
    return t_INVALID_SERIAL_NUMBER.toStdString();

  if (auto s = activate(serialNumber)) {
    if (s == E_ACTIVATESN_LIMIT_MET)
      return t_TOO_MANY_ACTIVATIONS.toStdString();
    auto code = String(static_cast<int>(s));
    return (t_UNABLE_TO_ACTIVATE + code).toStdString();
  }

  Activation activation;
  activation.set_samples(crypt(serialNumber));
  activation.set_frame(crypt(name));
  activation.set_rate(fromTimeDays(0));
  data::setProto(activation);
#endif

  return "";
}

}  // namespace ews
}  // namespace util
}  // namespace rec

#endif
