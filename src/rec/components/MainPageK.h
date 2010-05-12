#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include "JuceLibraryCode/JuceHeader.h"
#include "DemoThumbnailComp.h"
#include "rec/base/scoped_ptr.h"
#include "rec/audio/source/Stretchable.h"
#include "rec/audio/source/Loop.h"

class MainPageJ;

class MainPageK : public FileBrowserListener {
 public:
  MainPageK(AudioDeviceManager* d);
  ~MainPageK() {}

  void construct(MainPageJ* peer);
  void destruct();

  void startStopButtonClicked();
  void loopingButtonClicked();
  void zoomSliderChanged(double value);

  void selectionChanged();
  void fileClicked(const File& file, const MouseEvent& e) {}
  void fileDoubleClicked(const File& file) {}

  DirectoryContentsList* directoryList() { return &directoryList_; }

 private:
  static const int READAHEAD_SIZE = 32768;
  static const int LOOP_BUFFER_SIZE = 65536;
  static const int LOOP_BUFFER_WRAPAROUND = 32736;
  static const int LOOP_BUFFER_CHANNELS = 2;
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

  // Contains the entire sample in memory, plus a wraparound.
  scoped_ptr<AudioSampleBuffer> loopBuffer_;

  // Contains the time-shifted sample in memory.
  scoped_ptr<AudioSampleBuffer> shiftedBuffer_;

  // Sends audio to the Stretchable source.
  scoped_ptr<rec::audio::source::Loop> loop_;

  // Sends audio to the transport source.
  scoped_ptr<rec::audio::source::Stretchable> stretchable_;

  // Sends audio to the AudioSourcePlayer.
  AudioTransportSource transportSource_;

  // Streams audio to an AudioIODevice.
  AudioSourcePlayer player_;

  // Receives the final audio!
  AudioDeviceManager* deviceManager_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};


#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
