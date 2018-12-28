#include "rec/gui/proto/Custom.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

namespace rec {
namespace gui {

std::unique_ptr<Component> makeCustom(const Context& context) {
    auto& custom = context.component_.custom();
    std::unique_ptr<Component> component;
    if (auto maker = context.constants_.getMaker(custom.type_name()))
        component = maker(custom.data());
    return component;
}

}  // namespace gui
}  // namespace rec
