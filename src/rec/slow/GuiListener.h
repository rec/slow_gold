#ifndef __REC_SLOW_GUILISTENER__
#define __REC_SLOW_GUILISTENER__

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
  unique_ptr<juce::TooltipWindow> tooltipWindow_;
  bool displayHelpPane_;
  Component* lastComponent_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(GuiListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GUILISTENER__
