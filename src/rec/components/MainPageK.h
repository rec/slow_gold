#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <vector>

#include "JuceLibraryCode/JuceHeader.h"

#include "rec/audio/source/BufferedPositionable.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/base/scoped_ptr.h"
#include "rec/components/AudioThumbnailComponent.h"
#include "rec/persist/AutosaveApp.h"

class MainPageJ;

// It's generally a bad idea to use "using" in a header file, but this header
// has only limited use.
using rec::audio::timescaler::Description;
using rec::persist::Data;
using rec::audio::source::Loop;

class MainPageK : public FileBrowserListener,
                  public SliderListener,
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

 private:
  static const int THREAD_PRIORITY = 3;

  static const TreeView::ColourIds BACKGROUND;
  static const Colour FOREGROUND;
  static const File::SpecialLocationType START_DIR;
  static const char* PREVIEW_THREAD_NAME;
  static const char* APP_DATA_FILE_NAME;

  void loadFileIntoTransport(const File& audioFile);
  void readyToPlay();
  bool scaleTime();

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

  // Describes how to stretch.
  Data<Description>* description_;

  std::vector<AudioCDBurner*> burners_;
  StringArray cdNames_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};


#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
