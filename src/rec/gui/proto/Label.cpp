#include "rec/gui/proto/Label.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

using namespace juce;

namespace rec {
namespace gui {

std::unique_ptr<Component> makeLabel(const Context& context) {
    auto& component = context.component_;
    auto& proto = component.label();
    std::unique_ptr<SimpleLabel> label(new SimpleLabel("", proto.text()));

    // TODO: prevent simplelable from setting the name.
    // TODO: font.
    return std::move(label);
}

}  // namespace gui
}  // namespace rec
