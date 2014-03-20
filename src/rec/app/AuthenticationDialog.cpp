#include "rec/app/AuthenticationDialog.h"
#include "rec/data/DataOps.h"
#include "rec/program/Program.h"
#include "rec/util/Crypt.h"
#include "rec/util/ews/Activation.pb.h"
#include "rec/util/ews/EWS.h"

using namespace juce;

namespace rec {
namespace app {

namespace {

inline Time toTime(const string& s) {
  return Time(String(crypt(s)).getLargeIntValue());
}

inline string fromTime(const Time& t) {
  return crypt(String(t.toMilliseconds()).toStdString());
}

}  // namespace

int daysToExpiration() {
  auto activation = data::getProto<ews::Activation>();
  if (activation.has_samples()) {
    if (ews::confirm(crypt(activation.samples()))) {
      LOG(INFO) << "Sample rate computed.";
      return AUTHORIZED;
    }

    LOG(ERROR) << "Couldn't understand sample rate \""
               << activation.samples() << "\"";
    return EXPIRED;
  }

  auto expiration = program::getProgram()->demoExpirationDays();
  auto now = Time::getCurrentTime();
  Time time = activation.has_rate() ? toTime(activation.rate()) : now;
  if (time > now) {
    LOG(ERROR) << "Sample time greater than now: "
               << time.toMilliseconds() << ", " << now.toMilliseconds();
    return EXPIRED;
  }
  activation.set_rate(fromTime(time));
  data::setProto(activation);
  auto remainingDays = expiration - static_cast<int>((now - time).inDays());
  return jmax(remainingDays, EXPIRED);
}

bool authenticate(const string& serialNumber) {
  return false;
}

}  // namespace app
}  // namespace rec
