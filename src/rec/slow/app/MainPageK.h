#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <set>
#include <vector>

#include "rec/audio/source/DoubleStretchyThread.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/StretchyFactory.h"
#include "rec/slow/Preferences.h"
#include "rec/util/listener/ChangeBroadcaster.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/AudioThumbnail.h"
#include "rec/widget/tree/NodeItem.h"
#include "rec/widget/Panes.h"

class MainPageJ;

namespace rec {
namespace slow {

class ChangeBroadcaster : public util::listener::ChangeBroadcaster<slow::proto::Preferences> {
 public:
  ChangeBroadcaster() {}
  virtual bool isChanged(const slow::proto::Preferences& x,
                         const slow::proto::Preferences& y) const {
    return x.track() != y.track();
  }
};

class MainPageK : public juce::Slider::Listener,
                  public juce::ChangeListener,
                  public widget::tree::NodeListener,
                  public util::listener::Listener<audio::source::Runny*> {
 public:
  MainPageK(juce::AudioDeviceManager* d);
  virtual ~MainPageK();

  void construct(MainPageJ* peer);
  void destruct();

  void startStopButtonClicked();
  void loopingButtonClicked();

  // SliderListener.
  virtual void sliderValueChanged(juce::Slider* slider);
  virtual void sliderDragEnded(juce::Slider* slider);

  // ChangeListener
  virtual void changeListenerCallback(void* objectThatHasChanged);

  // Listener<const VolumeFile&>
  virtual void operator()(const widget::tree::VolumeFile& file);

  // Listener<Runny*>
  virtual void operator()(audio::source::Runny* runny);

  void updateCursor();
  void loadRecentFile(int menuItemId);
  void cut();
  void paste();
  void start(bool isStart = true);
  bool ready() const;

  void loadFileIntoTransport(const widget::tree::VolumeFile& audioFile);

 private:
  static const int THREAD_PRIORITY = 3;
  static const int MINIMUM_SAMPLE_PRELOAD = 4096;

  static const File::SpecialLocationType START_DIR;
  static const char* PREVIEW_THREAD_NAME;
  juce::TimeSliceThread directoryListThread_;

  MainPageJ* peer_;

  // Sends audio to the AudioSourcePlayer.
  juce::AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  juce::AudioSourcePlayer player_;

  // Receives the final audio!
  juce::AudioDeviceManager* deviceManager_;

  typedef rec::audio::source::DoubleStretchyThread DoubleStretchyThread;
  typedef std::set<DoubleStretchyThread*> StretchySet;

  scoped_ptr<DoubleStretchyThread> stretchy_;
  StretchySet stretchyDeleter_;

  ChangeBroadcaster changeBroadcaster_;
  scoped_ptr<util::thread::ChangeLocker<slow::proto::Preferences> > changeLocker_;
  audio::source::StretchyFactory stretchyFactory_;
  scoped_ptr<audio::source::Runny> runny_;

  scoped_ptr<Thread> cursorThread_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
