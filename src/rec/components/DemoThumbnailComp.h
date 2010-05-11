#ifndef __THUMBNAIL_COMP
#define __THUMBNAIL_COMP

#include "juce_amalgamated.h"

namespace rec {

class DemoThumbnailComp  : public Component, public ChangeListener {
 public:
  DemoThumbnailComp()
      : thumbnailCache (5),
        thumbnail(512, formatManager, thumbnailCache) {
    startTime = endTime = 0;
    formatManager.registerBasicFormats();
    thumbnail.addChangeListener(this);
  }

  ~DemoThumbnailComp() {
    thumbnail.removeChangeListener(this);
  }

  void setFile(const File& file) {
    thumbnail.setSource(new FileInputSource(file));
    startTime = 0;
    endTime = thumbnail.getTotalLength();
  }

  void setZoomFactor(double amount) {
    if (thumbnail.getTotalLength() > 0) {
      double timeElapsed = thumbnail.getTotalLength() - startTime;
      double timeDisplayed = timeElapsed * (1.0 - jlimit(0.0, 1.0, amount));
      endTime = startTime + std::max(0.001, timeDisplayed);
      repaint();
    }
  }

  void mouseWheelMove(const MouseEvent& e, float wheelIncrementX,
                      float wheelIncrementY) {
    if (thumbnail.getTotalLength() > 0) {
      double newStart = startTime +(wheelIncrementX + wheelIncrementY) *(endTime - startTime) / 10.0;
      newStart = jlimit(0.0, thumbnail.getTotalLength() -(endTime - startTime), newStart);
      endTime = newStart +(endTime - startTime);
      startTime = newStart;
      repaint();
    }
  }

  void paint(Graphics& g) {
    g.fillAll(Colours::white);

    g.setColour(Colours::mediumblue);

    if (thumbnail.getTotalLength() > 0) {
      int heightPerChannel =(getHeight() - 4) / thumbnail.getNumChannels();

      for (int i = 0; i < thumbnail.getNumChannels(); ++i) {
        thumbnail.drawChannel(g, 2, 2 + heightPerChannel * i,
                              getWidth() - 4, heightPerChannel,
                              startTime, endTime,
                              i, 1.0f);
      }
    } else {
      g.setFont(14.0f);
      g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(), Justification::centred, 2);
    }
  }

  // this method is called by the thumbnail when it has changed, so we should repaint it..
  void changeListenerCallback(void*) {
    repaint();
  }

  AudioFormatManager formatManager;
  AudioThumbnailCache thumbnailCache;
  AudioThumbnail thumbnail;
  double startTime, endTime;
};

}  // namespace rec

#endif
