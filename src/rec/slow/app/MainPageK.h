#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <vector>

#include "rec/slow/Preferences.h"
#include "rec/audio/source/DoubleStretchyThread.h"
#include "rec/widget/AudioThumbnail.h"

#include "JuceLibraryCode/JuceHeader.h"

class MainPageJ;

namespace rec {
namespace slow {

class MainPageK : public juce::FileBrowserListener,
                  public juce::Slider::Listener,
                  public juce::ChangeListener {
 public:
  MainPageK(juce::AudioDeviceManager* d);
  ~MainPageK() {}

  void construct(MainPageJ* peer);
  void destruct();

  void startStopButtonClicked();
  void loopingButtonClicked();

  // SliderListener.
  virtual void sliderValueChanged(juce::Slider* slider);
  virtual void sliderDragEnded(juce::Slider* slider);

  // ChangeListener
  virtual void changeListenerCallback(void* objectThatHasChanged);

  // FileBrowserListener
  virtual void selectionChanged();
  virtual void fileClicked(const File& file, const juce::MouseEvent& e) {}
  virtual void fileDoubleClicked(const File& file) {}

  juce::DirectoryContentsList* directoryList() { return &directoryList_; }
  void updateCursor();
  void loadRecentFile(int menuItemId);
  void cut();
  void paste();

 private:
  static const int THREAD_PRIORITY = 3;

  static const juce::TreeView::ColourIds BACKGROUND;
  static const juce::Colour FOREGROUND;
  static const File::SpecialLocationType START_DIR;
  static const char* PREVIEW_THREAD_NAME;

  void loadFileIntoTransport(const File& audioFile);
  void readyToPlay();

  MainPageJ* peer_;

  // The directory list also handles the thumbnail updates.
  juce::TimeSliceThread directoryListThread_;
  juce::DirectoryContentsList directoryList_;

  // Sends audio to the AudioSourcePlayer.
  juce::AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  juce::AudioSourcePlayer player_;

  // Receives the final audio!
  juce::AudioDeviceManager* deviceManager_;

  typedef rec::audio::source::DoubleStretchyThread DoubleStretchyThread;
  scoped_ptr<DoubleStretchyThread> stretchy_;
  scoped_ptr<DoubleStretchyThread> stretchyDeleter_;

  scoped_ptr<Thread> cursorThread_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
