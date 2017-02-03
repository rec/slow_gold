#include "rec/gui/proto/TimeDial.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"
#include "rec/widget/status/DialComponent.h"
namespace rec {
namespace gui {

std::unique_ptr<Component> makeTimeDial(const Context& context) {
    using widget::status::time::DialComponent;
    return std::unique_ptr<Component>(new DialComponent(
            context.component_.time_dial()));
}

}  // namespace gui
}  // namespace rec
