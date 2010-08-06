#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include <vector>

#include "JuceLibraryCode/JuceHeader.h"
#include "AudioThumbnailComponent.h"
#include "rec/base/scoped_ptr.h"
#include "rec/audio/stretch/SimpleStretcher.h"
#include "rec/audio/source/Loop.h"
#include "rec/persist/Persist.h"

class MainPageJ;

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

  void loadFileIntoTransport(const File& audioFile);
  void readyToPlay();
  bool scaleTime();

  MainPageJ* peer_;

  // The directory list also handles the thumbnail updates.
  TimeSliceThread directoryListThread_;
  DirectoryContentsList directoryList_;

  // Contains the entire sample in memory, plus a wraparound.
  scoped_ptr<AudioSampleBuffer> loopBuffer_;

  // Contains the time-scaled sample in memory.
  scoped_ptr<AudioSampleBuffer> scaledBuffer_;

  // Sends audio to the Stretchable source.
  scoped_ptr<rec::audio::source::Loop> loop_;

  // Sends audio to the AudioSourcePlayer.
  AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  AudioSourcePlayer player_;

  // Receives the final audio!
  AudioDeviceManager* deviceManager_;

  typedef rec::audio::timescaler::Description Description;
  typedef rec::persist::Persistent<Description, google::protobuf::Message>
    ScaleDescription;

  // Describes how to stretch.
  ScaleDescription scaleDescription_;

  rec::audio::timescaler::Simple stretch_;
  std::vector<AudioCDBurner*> burners_;
  StringArray cdNames_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};


#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
