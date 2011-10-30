#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <vector>

#include "rec/gui/layout/Layout.h"
#include "rec/gui/SetterResizer.h"

namespace rec {

namespace gui {
class SetterResizer;
}

namespace slow {

class Components;

class MainPage : public gui::Layout {
 public:
  MainPage(Components*, data::Editable*);
  virtual ~MainPage();

  void paint(Graphics&);
  void setActive(bool a);

 private:
  gui::Layout mainPanel_;

  gui::SetterResizer directoryResizer_;
  gui::SetterResizer waveformResizer_;
  gui::SetterResizer loopResizer_;

  double length_;

  DISALLOW_COPY_AND_ASSIGN(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
