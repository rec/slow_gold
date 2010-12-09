#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <set>
#include <vector>

#include "rec/audio/source/DoubleRunny.h"
#include "rec/slow/Preferences.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/AudioThumbnail.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/Panes.h"

class MainPageJ;

using namespace rec::audio::source;
using namespace rec::util::listener;
using namespace rec::util::thread;
using namespace rec::widget::tree;

namespace rec {
namespace slow {

typedef slow::proto::Preferences Preferences;

class MainPageK : public Slider::Listener,
                  public ChangeListener,
                  public NodeListener,
                  public Listener<const Preferences&>,
                  public Listener<Source*>,
                  public Listener<double> {
 public:
  MainPageK(AudioDeviceManager* manager);
  virtual ~MainPageK();

  void construct(MainPageJ* peer);
  void destruct();

  void startStopButtonClicked();

  // SliderListener.
  virtual void sliderValueChanged(Slider* slider);

  // ChangeListener
  virtual void changeListenerCallback(ChangeBroadcaster* objectThatHasChanged);

  virtual void operator()(const VolumeFile& file);
  virtual void operator()(const Preferences& prefs);
  virtual void operator()(double cursorRatio);
  virtual void operator()(Source* runny);

  void updateCursor();
  void loadRecentFile(int menuItemId);
  void cut();
  void paste();
  void start(bool isStart = true);

  void loadFileIntoTransport(const VolumeFile& audioFile);

 private:
  static const int THREAD_PRIORITY = 3;
  static const int MINIMUM_SAMPLE_PRELOAD = 4096;

  static const File::SpecialLocationType START_DIR;
  static const char* PREVIEW_THREAD_NAME;

  MainPageJ* peer_;

  // Sends audio to the AudioSourcePlayer.
  AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  AudioSourcePlayer player_;

  // Receives the final audio!
  AudioDeviceManager* deviceManager_;

  scoped_ptr<ChangeLocker<Preferences> > changeLocker_;
  DoubleRunny doubleRunny_;

  scoped_ptr<Thread> cursorThread_;
  slow::proto::Preferences prefs_;
  int newPosition_;
  CriticalSection lock_;
  int samplePosition_;
  bool transportSourceSet_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
