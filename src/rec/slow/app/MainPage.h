#ifndef __REC_COMPONENT_MAIN_PAGE_J_H__
#define __REC_COMPONENT_MAIN_PAGE_J_H__

#include <set>
#include <set>
#include <vector>

#include <glog/logging.h>

#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/slow/Preferences.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/widget/Panes.h"
#include "rec/widget/status/Time.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/gui/SetterSlider.h"

using audio::source::Source;
using audio::source::TimeStretch;
using namespace rec::audio::source;
using namespace rec::slow::proto;
using namespace rec::util::thread;
using namespace rec::widget::tree;
using namespace rec::gui;

using persist::copy;
using util::thread::ThreadDescription;
using widget::waveform::WaveformProto;

namespace rec {
namespace slow {

class MainPageJ : public Component,
                  public ButtonListener,
                  public Listener<const Preferences&>,
                  public Listener<const VolumeFile&> {
 public:
  MainPageJ(AudioDeviceManager& deviceManager);
  virtual ~MainPageJ() ()

  void paint(Graphics& g);
  void resized();
  void buttonClicked(Button* buttonThatWasClicked);

  virtual void operator()(const VolumeFile& file);
  virtual void operator()(const Preferences& prefs);

  void loadRecentFile(int menuItemId);

 private:
  using widget::waveform::Cursor;
  using widget::waveform::Waveform;
  using widget::status::time::TextComponent;
  using widget::status::time::DialComponent;
  using widget::tree::Root;

  Waveform waveform_;
  TextButton startStopButton_;
  scoped_ptr<Root> treeRoot_;
  Label explanation_;
  SetterSlider timeScaleSlider_;
  SetterSlider pitchScaleSlider_;
  TextComponent songTime_;
  TextComponent realTime_;
  DialComponent songDial_;
  DialComponent realDial_;
  Cursor* cursor_;

  CriticalSection lock_;
  AudioTransportSourcePlayer transportSource_;
  scoped_ptr<ChangeLocker<Preferences> > changeLocker_;
  DoubleRunnyBuffer doubleRunny_;

  slow::proto::Preferences prefs_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(MainPageJ);
};

}  // namespace slow
}  // namespace rec


#endif   // __REC_COMPONENT_MAIN_PAGE_J_H__
