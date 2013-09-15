#include "rec/gui/proto/Layout.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<Layout> makeLayout(const LayoutProto& proto) {
  Orientation o = (proto.orientation() == LayoutProto::HORIZONTAL) ?
    HORIZONTAL : VERTICAL;
  unique_ptr<Layout> layout(new Layout(proto.name(), o,
                                       proto.resize_other_dimension()));
  return std::move(layout);
}

}  // namespace gui
}  // namespace rec
