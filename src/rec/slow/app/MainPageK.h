#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <set>
#include <vector>

#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/slow/Preferences.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/widget/Panes.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::audio::source;
using namespace rec::slow::proto;
using namespace rec::util::listener;
using namespace rec::util::thread;
using namespace rec::widget::tree;

namespace rec {
namespace slow {

class MainPageJ;

class MainPageK : public Slider::Listener,
                  public ChangeListener,
                  public Listener<PositionableAudioSource*>,
                  public Listener<const Preferences&>,
                  public Listener<const VolumeFile&>,
                  public Listener<float> {
 public:
  MainPageK(AudioDeviceManager* manager);
  virtual ~MainPageK();

  void construct(MainPageJ* peer);
  void destruct();

  void startStopButtonClicked();

  // SliderListener.
  virtual void sliderValueChanged(Slider* slider);

  // ChangeListener
  virtual void changeListenerCallback(ChangeBroadcaster* obj);

  virtual void operator()(const VolumeFile& file);
  virtual void operator()(const Preferences& prefs);
  virtual void operator()(PositionableAudioSource* source);

  void loadRecentFile(int menuItemId);
  void cut();
  void paste();
  void start(bool isStart = true);

  void loadFileIntoTransport(const VolumeFile& audioFile);

 private:
  MainPageJ* peer_;

  // Sends audio to the AudioSourcePlayer.
  AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  AudioSourcePlayer player_;

  // Receives the final audio!
  AudioDeviceManager* deviceManager_;

  scoped_ptr<ChangeLocker<Preferences> > changeLocker_;
  DoubleRunnyBuffer doubleRunny_;

  slow::proto::Preferences prefs_;
  CriticalSection lock_;
  bool transportSourceSet_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
