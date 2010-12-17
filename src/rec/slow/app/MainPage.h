#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <set>
#include <vector>

#include <glog/logging.h>

#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/slow/Preferences.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/listener/SetterListener.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/widget/Panes.h"
#include "rec/widget/status/Time.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/SetterSlider.h"

using namespace rec::audio::source;
using namespace rec::gui;
using namespace rec::slow::proto;
using namespace rec::util::thread;
using namespace rec::widget::status::time;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

using rec::persist::copy;

namespace rec {
namespace slow {

class MainPage : public Component,
                 public ButtonListener,
                 public listener::Listener<PositionableAudioSource*>,
                 public listener::Listener<const Preferences&> {
 public:
  MainPage(AudioDeviceManager& deviceManager);
  virtual ~MainPage();

  void paint(Graphics& g);
  void resized();
  void buttonClicked(Button* buttonThatWasClicked);

  virtual void operator()(const Preferences& prefs);
  // TODO: remove?
  virtual void operator()(PositionableAudioSource*) {}

  void loadRecentFile(int menuItemId);

 private:
  Waveform waveform_;
  TextButton startStopButton_;
  scoped_ptr<Root> treeRoot_;
  Label explanation_;
  SetterSlider<Preferences> timeScaleSlider_;
  SetterSlider<Preferences> pitchScaleSlider_;
  TextComponent songTime_;
  DialComponent songDial_;
  Cursor* cursor_;

  CriticalSection lock_;
  app::AudioTransportSourcePlayer transportSource_;
  scoped_ptr<ChangeLocker<Preferences> > changeLocker_;
  scoped_ptr<DoubleRunnyBuffer> doubleRunny_;
  listener::SetterListener<const VolumeFile&> fileListener_;

  slow::proto::Preferences prefs_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPage);
};

}  // namespace slow
}  // namespace rec


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
