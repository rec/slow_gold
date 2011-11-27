#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <vector>

#include "rec/gui/layout/Layout.h"
#include "rec/gui/SetterResizer.h"
#include "rec/gui/DropTarget.h"

namespace rec {

namespace gui {
class SetterResizer;
}

namespace slow {

class Components;

class MainPage {
 public:
  MainPage(Components*, data::Editable*);
  virtual ~MainPage();

  gui::Layout* panel() { return &mainPanel_; }

#if 0
  Broadcaster<const gui::DropFiles&>* dropBroadcaster() {
    return mainPanel_.dropBroadcaster();
  }
#endif

 private:
  // mainPanel_ contains navigationPanel_, the waveform and playbackPanel_.
  gui::Layout mainPanel_;

  // navigationPanel_ contains the navigator, song metadata and loops.
  gui::Layout navigationPanel_;

  // playbackPanel_ contains help, transform and the controls.
  gui::Layout playbackPanel_;
  gui::Layout helpPanel_;
  gui::Layout transformPanel_;
  gui::Layout controlPanel_;

  // Resizers for mainPanel_;
  gui::SetterResizer navigationResizer_;
  gui::SetterResizer waveformResizer_;

  // Resizers for navigationPanel_.
  gui::SetterResizer directoryResizer_;
  gui::SetterResizer metadataResizer_;

  // Resizers for playbackPanel_.
  gui::SetterResizer helpResizer_;
  gui::SetterResizer transformResizer_;
  gui::SetterResizer controlResizer_;

  double length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
