#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <vector>

#include "rec/gui/Layout.h"

namespace rec {

namespace gui {
class SetterResizer;
}

namespace slow {

class MainPage : public gui::Layout {
 public:
  MainPage();
  virtual ~MainPage();

  void paint(Graphics&);

 private:
  void addResizer(ptr<gui::SetterResizer>* r, const char* addr, Layout* lo);
  void doLayout();

  ptr<gui::SetterResizer> resizer_[2];
  ptr<gui::SetterResizer> loopResizer_;

  gui::Layout panel_;
  gui::Layout subpanel_;

  double length_;

  DISALLOW_COPY_AND_ASSIGN(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
