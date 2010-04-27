#ifndef __REC_COMPONENT_MAIN_PAGE_K_H__
#define __REC_COMPONENT_MAIN_PAGE_K_H__

#include "JuceLibraryCode/JuceHeader.h"
#include "DemoThumbnailComp.h"
#include "rec/base/scoped_ptr.h"
#include "rec/audio/source/Stretchable.h"

class MainPageJ;

class MainPageK : public FileBrowserListener {
 public:
  MainPageK(AudioDeviceManager* d)
    : deviceManager_(d),
      thread_("Timeslice"),
      directoryList_(NULL, thread_), 
      loopBuffer_(2, 65536) {
  }
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

  typedef rec::audio::source::Stretchable Stretchable;

  void loadFileIntoTransport(const File& audioFile);

  MainPageJ* peer_;

  AudioDeviceManager* deviceManager_;
  TimeSliceThread thread_;
  AudioTransportSource transportSource_;
  DirectoryContentsList directoryList_;

  scoped_ptr<AudioFormatReaderSource> source_;
  scoped_ptr<Stretchable> stretchable_;
  AudioSourcePlayer player_;

  AudioSampleBuffer loopBuffer_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};


#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
