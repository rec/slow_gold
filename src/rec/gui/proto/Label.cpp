#include "rec/gui/proto/Label.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<SimpleLabel> makeLabel(const LabelProto& proto, const Constants&) {
  unique_ptr<SimpleLabel> label(new SimpleLabel(proto.name(), proto.text()));
  label->setTooltip(proto.tooltip());
  // TODO: font.
  return std::move(label);
}

}  // namespace gui
}  // namespace rec
