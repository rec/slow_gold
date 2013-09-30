#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>

#include "rec/gui/SetterResizer.h"
#include "rec/gui/proto/Panel.h"

namespace rec {

namespace slow { class Components; }

namespace slow {

class MainPage {
 public:
  MainPage();
  virtual ~MainPage();

  void layoutComponents(Components*);
  gui::Panel* panel() { return mainPanel_.get(); }

 private:
  Components* components_;

  // mainPanel_ contains navigationPanel_, the waveform and playbackPanel_.
  unique_ptr<gui::Panel> mainPanel_;

  // navigationPanel_ contains the navigator, song metadata and loops.
  gui::Panel navigationPanel_;

  // playbackPanel_ contains help, transform and the controls.
  gui::Panel playbackPanel_;
  gui::Panel transformPanel_;

  // Resizers for mainPanel_;
  gui::SetterResizer navigationResizer_;

  // Resizers for navigationPanel_.
  gui::SetterResizer directoryResizer_;
  gui::SetterResizer metadataResizer_;

  // Resizers for playbackPanel_.
  gui::SetterResizer helpResizer_;
  gui::SetterResizer transformResizer_;

  unique_ptr<Component> helpPanel_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
