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
    doubleMap_[constant.name()] = constant.value();
}

double Constants::getDouble(const string& name) const {
  if (isNumber(name))
    return str(name).getDoubleValue();

  try {
    return doubleMap_.at(name);
  } catch (std::out_of_range&) {
    LOG(ERROR) << "Don't understand constant " << name;
    return 0.0;
  }
}

Constants::ComponentMaker Constants::getMaker(const string& name) const {
  try {
    return componentMakerMap_.at(name);
  } catch (std::out_of_range&) {
    LOG(ERROR) << "Don't understand maker " << name;
    return nullptr;
  }
}

void Constants::addMaker(const string& name, ComponentMaker maker) {
  DCHECK(not componentMakerMap_.count(name)) << "Duplicate maker for " << name;
  componentMakerMap_[name] = maker;
}

}  // namespace gui
}  // namespace rec
