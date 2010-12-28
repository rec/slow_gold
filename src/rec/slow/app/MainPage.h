#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <set>
#include <vector>

#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/data/persist/Copy.h"
#include "rec/gui/SetterSlider.h"
#include "rec/gui/DropTarget.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/listener/SetterListener.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/widget/status/Time.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::audio::source;
using namespace rec::audio;
using namespace rec::gui;
using namespace rec::util::thread;
using namespace rec::widget::status::time;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

using rec::persist::copy;

namespace rec {
namespace slow {

class MainPage : public Component,
                 public ButtonListener,
                 public listener::Listener<const float&>,
                 public listener::Listener<const TimeAndMouseEvent&>,
                 public listener::Listener<const VolumeFile&> {
 public:
  MainPage(AudioDeviceManager&);
  virtual ~MainPage() {}

  void paint(Graphics&);
  void resized();
  void buttonClicked(Button*);

  virtual void operator()(const TimeAndMouseEvent& timeMouse);
  virtual void operator()(const float& time);
  virtual void operator()(const VolumeFile& file);

  void doOpen();
  void doClose();

 private:
  typedef thread::ChangeLocker<float> TimeLocker;
  typedef thread::ChangeLocker<VolumeFile> FileLocker;

  thread_ptr<app::AudioTransportSourcePlayer> transportSource_;
  Waveform waveform_;
  DropTarget waveformTarget_;
  TextButton startStopButton_;
  thread_ptr<Root> treeRoot_;

  class DirectoryDropTarget : public DropTarget {
   public:
    virtual bool isInterestedInFileDrag(const StringArray&) { return true; }
  };

  DirectoryDropTarget treeRootTarget_;
  Label explanation_;

  SetterSlider<StretchyProto> timeScaleSlider_;
  SetterSlider<StretchyProto> pitchScaleSlider_;
  TextComponent songTime_;
  DialComponent songDial_;
  Cursor* cursor_;

  CriticalSection lock_;
  VolumeFile file_;
  thread_ptr<DoubleRunnyBuffer> doubleRunny_;
  persist::Data<StretchyProto>* stretchy_;
  thread_ptr<TimeLocker> timeLocker_;
  thread_ptr<FileLocker> fileLocker_;

  listener::SetterListener<const VolumeFile&> fileListener_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__


