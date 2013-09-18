#include "rec/gui/proto/Label.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Component> makeLabel(const ComponentProto& component,
                                const Constants& constants) {
  auto& proto = component.label();
  unique_ptr<SimpleLabel> label(new SimpleLabel("", proto.text()));

  // TODO: prevent simplelable from setting the name.
  // TODO: font.
  return std::move(label);
}

}  // namespace gui
}  // namespace rec
