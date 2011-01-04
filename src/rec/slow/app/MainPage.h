#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <set>
#include <vector>

#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/data/persist/Copy.h"
#include "rec/gui/DropTarget.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/StretchyController.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/listener/SetterListener.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/widget/status/Time.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Waveform.h"

using namespace juce;

using namespace rec::audio::source;
using namespace rec::audio;
using namespace rec::gui;
using namespace rec::slow::app;
using namespace rec::util::thread;
using namespace rec::widget::status::time;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

using rec::persist::copy;

namespace rec {
namespace slow {

class MainPage : public Component,
                 public juce::ButtonListener,
                 public Listener<const float&>,
                 public Listener<float>,
                 public Listener<const TimeAndMouseEvent&>,
                 public Listener<const VolumeFile&>,
                 public Listener<const AudioTransportSourcePlayer&>,
                 public Broadcaster<float> {
 public:
  MainPage(AudioDeviceManager&);

  virtual ~MainPage();

  void paint(Graphics&);
  void resized();
  void buttonClicked(Button*);

  // Callback from someone clicking in the waveform.
  virtual void operator()(const TimeAndMouseEvent& timeMouse);

  // Callback from the AudioTransport.
  virtual void operator()(float time);

  // Callback when we're ready to actually jump to that new time.
  virtual void operator()(const float& time);

  // The player has started or stopped.
  virtual void operator()(const AudioTransportSourcePlayer& player);

  virtual void operator()(const VolumeFile& file);

  void doOpen();
  void doClose();
  void clearTime();
  void setButtonState();

  virtual bool keyPressed(const juce::KeyPress& kp) {
    if (kp.getTextCharacter() == ' ') {
      transportSource_->toggle();
      return true;
    }
    return false;
  }

 private:
  typedef thread::ChangeLocker<float> TimeLocker;
  typedef thread::ChangeLocker<VolumeFile> FileLocker;

  thread_ptr<app::AudioTransportSourcePlayer> transportSource_;
  DropTarget<Waveform, WaveformProto> waveform_;
  juce::DrawableButton startStopButton_;
  gui::SetterToggle<StretchyProto> disableButton_;
  thread_ptr<Root> treeRoot_;

  gui::StretchyController stretchyController_;
  TextComponent songTime_;
  DialComponent songDial_;
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
