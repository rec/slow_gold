#include "rec/widget/status/Status.h"
#include "rec/widget/status/Status.pb.h"
#include "rec/widget/Painter.h"
#include "rec/widget/Widget.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace widget {
namespace status {
#if 0
namespace {

const StatusDesc& getOrDefault(const StatusDesc* desc) {
  static util::Defaulter<StatusDesc> d("");
  return d.get(desc);
}

}  // namespace


Status::Status(const StatusDesc* desc)
    : desc_(getOrDefault(desc, initStatusDesc)),
      time_(addChildWidget(this, desc_->time())),
      dial_(addChildWidget(this, desc_->dial())) {
}

void Status::paint(juce::Graphics& g) {
  Painter p(desc_->widget(), &g);
}

#endif
}  // namespace status
}  // namespace widget
}  // namespace rec
