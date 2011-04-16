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
class MainPage : public gui::Layout,
                 public Listener<double>,
                 public Listener<const TimeAndMouseEvent&>,
                 public Listener<const SelectionRange&>,
                 public Listener<const VirtualFile&> {
 public:
  MainPage(Instance* instance);
  virtual ~MainPage();

  void paint(Graphics&);

  virtual void operator()(const TimeAndMouseEvent&);
  virtual void operator()(const VirtualFile&);
  virtual void operator()(double time);
  virtual void operator()(const SelectionRange&);

  void clearTime();
  void clearSelection();
  void clearLoops();

  void addLoopPoint();
  void zoomIn(const TimeAndMouseEvent& timeMouse);
  void zoomOut();

  void loadRecentFile(int menuItemId);
  void cut();
  void paste();
  gui::AudioSetupPage* audioSetupPage() { return &audioSetupPage_; }

 private:
  void addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo);
  void doLayout();

  persist::Data<ZoomProto>* zoomProto() { return instance_->data().zoomProto_; }

  Instance* const instance_;

  thread_ptr<widget::tree::Root> directoryTreeRoot_;
  Waveform waveform_;
  gui::Loops loops_;
  PlaybackController playbackController_;

  ptr<SetterResizer> resizer_[2];
  ptr<SetterResizer> loopResizer_;

  gui::Layout panel_;
  gui::Layout subpanel_;

  double length_;

  gui::AudioSetupPage audioSetupPage_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);

  // DropTarget<Waveform, WaveformProto> waveform_;  // turn off dropping for now...
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
