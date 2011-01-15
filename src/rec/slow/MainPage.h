#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <vector>

#include "rec/gui/Layout.h"
#include "rec/gui/Loops.h"
#include "rec/gui/SetterResizer.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/StretchyPlayer.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::gui;
using namespace rec::widget::waveform;

using rec::audio::source::LoopPointList;
using rec::widget::tree::Root;

namespace rec {
namespace slow {


class MainPage : public gui::Layout,
                 public Listener<const TimeAndMouseEvent&>,
                 public Listener<const VirtualFile&> {
 public:
  MainPage(AudioDeviceManager*);
  virtual ~MainPage();

  void paint(Graphics&);

  // Callback from someone clicking in the waveform.
  virtual void operator()(const TimeAndMouseEvent& timeMouse);

  // Callback when a new file has been installed.
  virtual void operator()(const VirtualFile& file);

  void doOpen();
  void doClose();
  void clearTime();

  virtual bool keyPressed(const juce::KeyPress& kp);

 private:
  void addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo);
  void addLoopPoint();

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

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
