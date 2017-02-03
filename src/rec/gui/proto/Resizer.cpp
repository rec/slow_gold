#include "rec/gui/proto/Resizer.h"
#include "rec/gui/SetterResizer.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

std::unique_ptr<Component> makeResizer(const Context& context, bool isSimple) {
    auto& component = context.component_;
    data::Address address;
    string minValue;
    if (isSimple) {
        address = context.address_;
        address.add_part()->set_name(component.resizer());
        minValue = component.min_resizer();
    } else {
        address = component.address();
        minValue = component.full_resizer().min_value();
    }
    return std::unique_ptr<Component>(
            new SetterResizer(address,
                                                dynamic_cast<Panel*>(context.parent_),
                                                context.parent_->getNumChildComponents(),
                                                context.constants_.getDouble(minValue)));
}

}  // namespace

std::unique_ptr<Component> makeResizer(const Context& context) {
    return makeResizer(context, false);
}

std::unique_ptr<Component> makeSimpleResizer(const Context& context) {
    return makeResizer(context, true);
}

}  // namespace gui
}  // namespace rec
