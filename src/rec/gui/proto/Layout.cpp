#include "rec/gui/proto/Layout.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Panel> makeLayout(const LayoutProto& proto) {
  Orientation o = (proto.orientation() == LayoutProto::HORIZONTAL) ?
    HORIZONTAL : VERTICAL;
  return make_unique<Panel>(
      proto.name(), o, proto.resize_other_dimension(), proto.is_main());
}

}  // namespace gui
}  // namespace rec
