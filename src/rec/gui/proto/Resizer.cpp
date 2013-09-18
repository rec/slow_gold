#include "rec/gui/proto/Resizer.h"
#include "rec/gui/SetterResizer.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Component> makeResizer(const ComponentProto& component,
                                  const Constants& constants) {
  auto& proto = component.full_resizer();
  return unique_ptr<Component>(
      new SetterResizer(component.address(),
                        nullptr, // TODO
                        -1, // TODO
                        constants(proto.min_value())));

}

}  // namespace gui
}  // namespace rec
