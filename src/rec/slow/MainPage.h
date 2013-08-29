#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>

#include "rec/app/LanguageListener.h"
#include "rec/gui/layout/Layout.h"
#include "rec/gui/DropTarget.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/SetterResizer.h"

namespace rec {

namespace gui { class SetterResizer; }
namespace gui { class SimpleLabel; }
namespace slow { class Components; }

namespace slow {

class MainPage : public app::LanguageListener {
 public:
  MainPage(Components*);
  virtual ~MainPage();

  gui::Layout* panel() { return mainPanel_.get(); }
  void setTooltip(const String&);
  void setEnabled(bool);
  virtual void languageChanged();

 private:
  Components* components_;

  // mainPanel_ contains navigationPanel_, the waveform and playbackPanel_.
  ptr<gui::Layout> mainPanel_;

  // navigationPanel_ contains the navigator, song metadata and loops.
  gui::Layout navigationPanel_;

  // playbackPanel_ contains help, transform and the controls.
  gui::Layout playbackPanel_;
  gui::Layout helpPanel_;
  gui::Layout transformPanel_;
  gui::Layout controlPanel_;

  // Resizers for mainPanel_;
  gui::SetterResizer navigationResizer_;

  // Resizers for navigationPanel_.
  gui::SetterResizer directoryResizer_;
  gui::SetterResizer metadataResizer_;

  // Resizers for playbackPanel_.
  gui::SetterResizer helpResizer_;
  gui::SetterResizer transformResizer_;

  gui::SimpleLabel helpCaption_;
  gui::SimpleLabel helpBody_;
  double length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
