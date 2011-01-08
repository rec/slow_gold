#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <set>
#include <vector>

#include "rec/data/persist/Copy.h"
#include "rec/gui/Layout.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/slow/app/PlaybackController.h"
#include "rec/slow/app/StretchyPlayer.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/SetterResizer.h"
#include "rec/util/thread/Trash.h"

using namespace juce;

using namespace rec::audio;
using namespace rec::audio::source;
using namespace rec::gui;
using namespace rec::util::thread;
using namespace rec::widget::status::time;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

using rec::persist::copy;

namespace rec {
namespace slow {

class MainPage : public gui::Layout,
                 public Listener<const TimeAndMouseEvent&>,
                 public Listener<const VolumeFile&> {
 public:
  MainPage(AudioDeviceManager*);
  virtual ~MainPage();

  void paint(Graphics&);

  // Callback from someone clicking in the waveform.
  virtual void operator()(const TimeAndMouseEvent& timeMouse);

  // Callback when a new file has been installed.
  virtual void operator()(const VolumeFile& file);

  void doOpen();
  void doClose();
  void clearTime();

  virtual bool keyPressed(const juce::KeyPress& kp);

 private:
  gui::Layout panel_;
  SetterResizer hbar_;
  SetterResizer vbar_;

  thread_ptr<Root> treeRoot_;
  DropTarget<Waveform, WaveformProto> waveform_;
  juce::Label loops_;
  Cursor* cursor_;
  bool openDialogOpen_;
  PlaybackController controller_;
  StretchyPlayer player_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
