#include "rec/gui/proto/Custom.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

namespace rec {
namespace gui {

unique_ptr<Component> makeCustom(
    const ComponentProto& proto, const Constants& constants) {
  auto& custom = proto.custom();
  unique_ptr<Component> component;
  if (auto maker = constants.getMaker(custom.type_name()))
    component = maker(custom.data());
  return std::move(component);
}

}  // namespace gui
}  // namespace rec
