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

Authentication testAuthenticated() {
  Authentication result;
  auto activation = data::getProto<ews::Activation>();
  if (activation.has_samples()) {
    result.serialNumber = crypt(activation.samples());
    if (ews::confirm(result.serialNumber)) {
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

bool authenticate(const string& serialNumber) {
  return false;
}

}  // namespace app
}  // namespace rec
