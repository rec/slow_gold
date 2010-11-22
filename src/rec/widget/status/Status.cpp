#include "rec/widget/status/Status.h"
#include "rec/widget/status/Status.pb.h"
#include "rec/widget/Painter.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace widget {
namespace status {

namespace {

void defaultStatusDesc(StatusDesc* desc) {
}

}  // namespace


Status::Status(const StatusDesc* desc)
    : desc_(util::getOrDefault(desc, defaultStatusDesc)),
      time_(desc_->time()),
      dial_(desc_->dial()) {
}

void Status::paint(juce::Graphics& g) {
  Painter p(desc_->widget(), &g);
}

}  // namespace status
}  // namespace widget
}  // namespace rec
