#include "rec/gui/proto/Time.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"
#include "rec/widget/status/TextComponent.h"

namespace rec {
namespace gui {

std::unique_ptr<Component> makeTime(const Context& context) {
    using widget::status::time::TextComponent;
    return std::unique_ptr<Component>(new TextComponent(context.component_.time()));
}

}  // namespace gui
}  // namespace rec
