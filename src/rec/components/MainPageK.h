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
      directoryList_(NULL, thread_) {
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
  typedef rec::audio::source::Stretchable Stretchable;

  void loadFileIntoTransport(const File& audioFile);

  MainPageJ* peer_;

  AudioDeviceManager* deviceManager_;
  TimeSliceThread thread_;
  AudioTransportSource transportSource_;
  DirectoryContentsList directoryList_;

  scoped_ptr<AudioFormatReaderSource> audioSource_;
  scoped_ptr<Stretchable> stretchable_;
  AudioSourcePlayer audioSourcePlayer_;

  DISALLOW_COPY_AND_ASSIGN(MainPageK);
};


#endif  // __REC_COMPONENT_MAIN_PAGE_K_H__
