#include "rec/gui/proto/Resizer.h"
#include "rec/gui/SetterResizer.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Component> makeResizer(const Context& context) {
  auto& component = context.component_;
  auto& proto = component.full_resizer();
  return unique_ptr<Component>(
      new SetterResizer(component.address(),
                        nullptr, // TODO
                        -1, // TODO
                        context.constants_.getDouble(proto.min_value())));

}

}  // namespace gui
}  // namespace rec
