#include "rec/gui/proto/Resizer.h"

using namespace juce;

namespace rec {
namespace gui {

unique_ptr<SetterResizer> makeResizer(const ResizerProto& proto,
                                      const Constants&) {
  unique_ptr<SetterResizer> resizer(
      new SetterResizer(proto.data_address().type_name(),
                        proto.data_address().address(),
                        nullptr, // TODO
                        -1, // TODO
                        proto.min_value()));

  return std::move(resizer);
}

}  // namespace gui
}  // namespace rec
