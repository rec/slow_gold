#include "rec/gui/proto/Text.h"

#include "rec/data/Address.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"
#include "rec/gui/SetterText.h"
#include "rec/program/Program.h"
#include "rec/program/JuceModel.h"
#include "rec/util/Binary.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

    
#ifdef UNUSED_CODE
void construct(std::unique_ptr<Drawable>* drawable, const string& name) {
    drawable->reset(constructName<Drawable>(name + "_svg"));
}
#endif

}  // namespace

std::unique_ptr<Component> makeText(const Context& context) {
    auto& component = context.component_;
    const TextProto& proto = component.text();
    return std::unique_ptr<Component>(
            new SetterText("(name)", component.address(), "(tt)",
                                          proto.caption(), not proto.caption().empty()));
}

}  // namespace gui
}  // namespace rec
