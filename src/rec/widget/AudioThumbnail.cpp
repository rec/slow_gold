#include <glog/logging.h>

#include "rec/widget/AudioThumbnail.h"
#include "rec/gui/Color.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/util/cd/CDReader.h"

using namespace juce;
using namespace rec::widget::tree;

namespace rec {
namespace widget {

AudioThumbnailWidget::AudioThumbnailWidget(const AudioThumbnailDesc& desc)
    : Component(desc.widget().name().c_str()),
      description_(desc),
      thumbnailCache_(description_.thumbnail_cache()),
      thumbnail_(description_.source_samples_per_thumbnail_sample(),
                 *AudioFormatManager::getInstance(), thumbnailCache_),
      thumbnailSet_(false) {
  startTime_ = endTime_ = cursor_ = ratio_ = 0;
  thumbnail_.addChangeListener(this);
}

AudioThumbnailWidget::~AudioThumbnailWidget() {
  thumbnail_.removeChangeListener(this);
}

class WriteThread : public Thread {
 public:
  WriteThread(const AudioThumbnail& thumbnail, const File& file)
      : thumbnail_(thumbnail), file_(file) {
  }

  void run() {
    string file = file_.getFullPath().toCString();
    if (!file_.getParentDirectory().createDirectory()) {
      LOG(ERROR) << "Can't make dir " << file;
    } else if (!file.deleteFile()) {
      LOG(ERROR) << "Can't delete file " << file;
    } else {
      scoped_ptr<OutputStream> out(file_.createOutputStream());
      if (out) {
        thumbnail.saveTo(*out);
        DLOG(INFO) << "Saved to file " << file;
      } else {
        LOG(ERROR) << "Can't create file " << file;
      }
    }

    trash::discard(this);
  }

 private:
  const AudioThumbnail& thumbnail_;
  const File& file_;
  DISALLOW_COPY_AND_ASSIGN(WriteThread);
};

void AudioThumbnailWidget::operator()(const AudioSourceChannelInfo& i) {
  if (!thumbnail_.fullyLoaded()) {
    thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);
    if (thumbnail_.fullyLoaded())
      new WriteThread(thumbnail_, getThumbnailFile()).startThread();
  }
}

File AudioThumbnailWidget::getThumbnailFile() {
  return getShadowDirectory(file_).getChildFile("thumbnail.stream");
}

#define USE_THUMBNAIL_WIDGETS false

void AudioThumbnailWidget::setFile(const VolumeFile& file) {
  ScopedLock l(lock_);
  file_ = file;
  startTime_ = ratio_ = 0;
  cursor_ = 0;
  thumbnail_.reset(2, 44100);

  File file = getThumbnailFile();
  thumbnailSet_ = false;
  if (file.exists()) {
    scoped_ptr<InputStream> in(file.createInputStream());
    if (in) {
      thumbnail_.loadFrom(*in);
      thumbnailSet_ = true;
    } else {
      LOG(ERROR) << "Unable to create input for " << file.getFullPath().toCString();
    }
  }

  scoped_ptr<AudioFormatReader> reader(createReader(file));
  endTime_ = reader.lengthInSamples / 44100;
  if (file_.volume().type() != tree::Volume::CD && !thumbnailSet_)
    thumbnail_.setSource(new FileInputSource(tree::getFile(file_)));
}

void AudioThumbnailWidget::setZoomFactor(double amount) {
  if (thumbnail_.getTotalLength() > 0) {
    double timeElapsed = thumbnail_.getTotalLength() - startTime_;
    double timeDisplayed = timeElapsed * (1.0 - jlimit(0.0, 1.0, amount));
    endTime_ = startTime_ + std::max(0.001, timeDisplayed);
    repaint();
  }
}

void AudioThumbnailWidget::mouseWheelMove(const MouseEvent& e,
                                          float incX, float incY) {
  return;
  // no idea what this does yet.  :-D
  if (thumbnail_.getTotalLength() > 0) {
    double newStart = startTime_ + (incX + incY) * (endTime_ - startTime_)
      / 10.0;
    newStart = jlimit(0.0, thumbnail_.getTotalLength() -
                      (endTime_ - startTime_), newStart);
    endTime_ = newStart + (endTime_ - startTime_);
    startTime_ = newStart;
    repaint();
  }
}

Rectangle<int> AudioThumbnailWidget::cursorRectangle() const {
  int margin = description_.widget().margin();
  int thickness = description_.cursor_thickness();

  double position = jlimit(startTime_, endTime_, cursor_);
  double ratio = (endTime_ == startTime_) ? 0 :
    (position - startTime_) / (endTime_ - startTime_);
  int width = (getWidth() - 2 * margin);
  int cursorX = (margin - thickness / 2) + width * ratio;
  // DLOG(INFO) << margin << "," << thickness << "," << width << "," << ratio;

  return Rectangle<int>(cursorX, margin, thickness, getHeight() - margin);
}

bool AudioThumbnailWidget::within(int x) const {
  return x >= startTime_ && x <= endTime_;
}

void AudioThumbnailWidget::mouseUp(const MouseEvent& e) {
  int margin = description_.widget().margin();
  int width = getWidth() - 2 * margin;
  double ratio = (e.x - margin) / (1.0 * width);
  broadcast(ratio);
  setCursor(ratio);
}

void AudioThumbnailWidget::setCursor(double cursorRatio) {
  // DLOG(INFO) << "Setting cursor " << cursorRatio;
  double cursor = cursorRatio * thumbnail_.getTotalLength();
  Rectangle<int> before, after;
  {
    ScopedLock l(lock_);
    ratio_ = cursorRatio;
    CHECK_EQ(ratio_, ratio_);
    before = cursorRectangle();
    cursor_ = cursor;
    CHECK_EQ(cursor, cursor);
    after = cursorRectangle();
  }

  if (before != after) {
    // TODO: fix cursor ghosting - expanding these rectangles doesn't do it!
    repaint(before);
    repaint(after);
  }
}

void AudioThumbnailWidget::paint(Graphics& g) {
  Painter p(description_.widget(), &g);
  int margin = p.margin();
  if (thumbnail_.getTotalLength() > 0) {
    int heightPerChannel = (getHeight() - 2 * margin) /
      thumbnail_.getNumChannels();

    for (int i = 0; i < thumbnail_.getNumChannels(); ++i) {
      juce::Rectangle<int> rect(margin, margin + heightPerChannel * i,
                                getWidth() - 2 * margin, heightPerChannel);
      thumbnail_.drawChannel(g, rect, startTime_, endTime_, i, 1.0f);
    }

    p.setColor(Painter::HIGHLIGHT);
    g.drawRect(cursorRectangle());

  } else {
    g.setFont(14.0f);
    g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(),
                     Justification::centred, margin);
  }
}

int AudioThumbnailWidget::getCursor() const {
  ScopedLock l(lock_);
  return cursor_;
}

double AudioThumbnailWidget::ratio() const {
  ScopedLock l(lock_);
  return ratio_;
}

}  // namespace widget
}  // namespace rec

