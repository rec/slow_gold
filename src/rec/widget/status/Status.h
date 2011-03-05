#ifndef __REC_WIDGET_STATUS_STATUS__
#define __REC_WIDGET_STATUS_STATUS__

#include <vector>

#include "rec/base/base.h"
#include "rec/widget/status/TextComponent.h"
#include "rec/widget/status/DialComponent.h"

namespace rec {
namespace widget {
namespace status {

class StatusDesc;

class Status : public juce::Component {
 public:
  explicit Status(const StatusDesc* desc);

  void paint(juce::Graphics& g);
  void setTime(double time);

 private:
  const StatusDesc* desc_;
  ptr<time::TextComponent> time_;
  ptr<time::DialComponent> dial_;
  juce::Label album_;
  juce::Label track_;
  // loop_indicator
  // transport

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Status);
};

}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_STATUS_STATUS__
