#pragma once

#include "rec/data/DataListener.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace slow {

class GuiSettings;

class GuiListener
    : public DataListener<GuiSettings>,
      public DataListener<widget::waveform::Viewport> {
 public:
  GuiListener();
  virtual ~GuiListener() {}

  void operator()(const GuiSettings&) override;
  void operator()(const widget::waveform::Viewport&) override;
  void update();

 private:
  CriticalSection lock_;
  std::unique_ptr<juce::TooltipWindow> tooltipWindow_;
  bool displayHelpPane_;
  Component* lastComponent_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(GuiListener);
};

}  // namespace slow
}  // namespace rec
