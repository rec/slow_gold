#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <vector>

#include "rec/slow/Preferences.h"
#include "rec/audio/source/DoubleStretchyThread.h"
#include "rec/gui/AudioThumbnailComponent.h"

#include "JuceLibraryCode/JuceHeader.h"

class MainPageJ;

namespace rec {
namespace slow {

class MainPageK : public FileBrowserListener,
                  public Slider::Listener,
                  public ChangeListener {
 public:
  MainPageK(AudioDeviceManager* d);
  ~MainPageK() {}

  void construct(MainPageJ* peer);
  void destruct();

  void startStopButtonClicked();
  void loopingButtonClicked();

  // SliderListener.
  virtual void sliderValueChanged(Slider* slider);
  virtual void sliderDragEnded(Slider* slider);

  // ChangeListener - for when CDs are inserted.
  virtual void changeListenerCallback(void* objectThatHasChanged);

  // FileBrowserListener
  virtual void selectionChanged();
  virtual void fileClicked(const File& file, const MouseEvent& e) {}
  virtual void fileDoubleClicked(const File& file) {}

  DirectoryContentsList* directoryList() { return &directoryList_; }
  void updateCursor();
  void setPosition(double position);
  void loadRecentFile(int menuItemId);
  void cut();
  void paste();

 private:
  static const int THREAD_PRIORITY = 3;

  static const TreeView::ColourIds BACKGROUND;
  static const Colour FOREGROUND;
  static const File::SpecialLocationType START_DIR;
  static const char* PREVIEW_THREAD_NAME;

  void loadFileIntoTransport(const File& audioFile);
  void readyToPlay();

  MainPageJ* peer_;

  // The directory list also handles the thumbnail updates.
  TimeSliceThread directoryListThread_;
  DirectoryContentsList directoryList_;

  // Sends audio to the AudioSourcePlayer.
  AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  AudioSourcePlayer player_;

  // Receives the final audio!
  AudioDeviceManager* deviceManager_;

  typedef rec::audio::source::DoubleStretchyThread DoubleStretchyThread;
  scoped_ptr<DoubleStretchyThread> stretchy_;
  scoped_ptr<DoubleStretchyThread> stretchyDeleter_;

  scoped_ptr<Thread> cursorThread_;

  std::vector<AudioCDBurner*> burners_;

  StringArray cdNames_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
