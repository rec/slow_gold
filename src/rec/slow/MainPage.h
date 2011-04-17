#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <vector>

#include "rec/audio/Device.h"
#include "rec/gui/Layout.h"
#include "rec/gui/Loops.h"
#include "rec/gui/SetterResizer.h"
#include "rec/slow/Instance.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/StretchyPlayer.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::gui;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

// MainPage contains StretchyPlayer, widget::tree::Root,
class MainPage : public gui::Layout {
 public:
  MainPage();
  virtual ~MainPage();

  void paint(Graphics&);

 private:
  void addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo);
  void doLayout();

  ptr<SetterResizer> resizer_[2];
  ptr<SetterResizer> loopResizer_;

  gui::Layout panel_;
  gui::Layout subpanel_;

  double length_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
