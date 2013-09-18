#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Constants.pb.h"

namespace rec {
namespace gui {

namespace {

bool isNumber(const string& s) {
  const char* p = s.c_str();
  for (; isdigit(*p); ++p);
  if (*p and *p++ != '.')
    return false;
  for (; isdigit(*p); ++p);
  return not *p;
}

}  // namespace

Constants::Constants(const ConstantProtos& protos) {
  for (auto& constant: protos.constant())
    map_[constant.name()] = constant.value();
}

double Constants::operator()(const string& name) const {
  if (isNumber(name))
    return str(name).getDoubleValue();

  try {
    return map_.at(name);
  } catch (std::out_of_range&) {
    LOG(ERROR) << "Don't understand constant " << name;
    return 0.0;
  }
}

}  // namespace gui
}  // namespace rec
