#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include "rec/slow/app/MainPageK.h"
#include "rec/widget/status/Time.h"
#include "rec/widget/tree/Root.h"

namespace rec {
namespace slow {

class MainPageJ  : public Component,
                   public ButtonListener,
                   public SliderListener {
 public:
  MainPageJ (AudioDeviceManager& deviceManager);
  ~MainPageJ();

  void loadRecentFile(int menuItemId) { peer_.loadRecentFile(menuItemId); }

  void paint (Graphics& g);
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void cut() { peer_.cut(); }
  void paste() { peer_.paste(); }

 private:
  using widget::waveform::Waveform;
  using widget::status::time::TextComponent;
  using widget::status::time::DialComponent;
  using widget::tree::Root;

  MainPageK peer_;
  Waveform waveform_;
  TextButton startStopButton_;
  FileTreeComponent fileTreeComp_;
  Root treeRoot_;
  Label explanation_;
  Slider timeScaleSlider_;
  Slider pitchScaleSlider_;
  TextComponent songTime_;
  TextComponent realTime;
  DialComponent songDial;
  DialComponent realDial;

  friend class MainPageK;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPageJ);
};

}  // namespace slow
}  // namespace rec


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
