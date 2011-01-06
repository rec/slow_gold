#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <set>
#include <vector>

#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/data/persist/Copy.h"
#include "rec/gui/Layout.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/slow/app/MainPageController.h"
#include "rec/util/listener/SetterListener.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/SetterResizer.h"

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
                 public Listener<const float&>,
                 public Listener<const TimeAndMouseEvent&>,
                 public Listener<const VolumeFile&> {
 public:
  MainPage(AudioDeviceManager&);
  virtual ~MainPage();

  void paint(Graphics&);

  // Callback from someone clicking in the waveform.
  virtual void operator()(const TimeAndMouseEvent& timeMouse);

  // Callback when we're ready to actually jump to a new time.
  virtual void operator()(const float& time);

  // Callback when we get a new file.
  virtual void operator()(const VolumeFile& file);

  void doOpen();
  void doClose();
  void clearTime();

  virtual bool keyPressed(const juce::KeyPress& kp);

 private:
  typedef thread::ChangeLocker<float> TimeLocker;
  typedef thread::ChangeLocker<VolumeFile> FileLocker;

  thread_ptr<AudioTransportSourcePlayer> transportSource_;

  gui::Layout panel_;
  SetterResizer hbar_;
  SetterResizer vbar_;

  thread_ptr<Root> treeRoot_;
  DropTarget<Waveform, WaveformProto> waveform_;
  juce::Label loops_;
  MainPageController controller_;

  Cursor* cursor_;

  CriticalSection lock_;
  VolumeFile file_;
  thread_ptr<DoubleRunnyBuffer> doubleRunny_;
  persist::Data<StretchyProto>* stretchy_;
  thread_ptr<TimeLocker> timeLocker_;
  thread_ptr<FileLocker> fileLocker_;

  SetterListener<const VolumeFile&> fileListener_;
  bool openDialogOpen_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
