#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <vector>

#include "rec/gui/Layout.h"
#include "rec/gui/Loops.h"
#include "rec/gui/SetterResizer.h"
#include "rec/slow/Broadcasters.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/StretchyPlayer.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::gui;
using namespace rec::widget::waveform;

using rec::widget::tree::Root;

namespace rec {
namespace slow {

class MainPage : public gui::Layout,
                 public Listener<double>,
                 public Listener<const TimeAndMouseEvent&>,
                 public Listener<const SelectionRange&>,
                 public Listener<const VirtualFile&> {
 public:
  MainPage(AudioDeviceManager*);
  virtual ~MainPage();

  void paint(Graphics&);

  virtual void operator()(const TimeAndMouseEvent&);
  virtual void operator()(const VirtualFile&);
  virtual void operator()(double time);
  virtual void operator()(const SelectionRange&);

  void doOpen();
  void doClose();
  void clearTime();
  void clearSelection();
  void clearLoops();

  virtual bool keyPressed(const juce::KeyPress& kp);
  void addLoopPoint();
  void zoomIn(const TimeAndMouseEvent& timeMouse);
  void zoomOut();

 private:
  void addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo);

  void doLayout();

  StretchyPlayer player_;

  ptr<SetterResizer> resizer_[2];
  ptr<SetterResizer> loopResizer_;

  thread_ptr<Root> directory_;
  DropTarget<Waveform, WaveformProto> waveform_;
  gui::Loops loops_;
  PlaybackController controller_;

  gui::Layout panel_;
  gui::Layout subpanel_;

  bool openDialogOpen_;
  double length_;
  persist::Data<ZoomProto>* zoomData_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
