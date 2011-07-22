#include "rec/audio/util/CachedThumbnail.h"

#include "rec/util/thread/FileWriter.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/util/AudioFormatManager.h"

using namespace juce;

namespace rec {
namespace audio {
namespace util {

CachedThumbnail::CachedThumbnail(const File& file, int compression, int length)
  : compression_(compression),
    cache_(1),
    cacheWritten_(false) {
  setFile(file, length);
}

void CachedThumbnail::setFile(const File& file, int length) {
  file_ = file;
  thumbnail_.reset(new AudioThumbnail(compression_,
                                      *rec::audio::getAudioFormatManager(),
                                      cache_));
  thumbnail_->reset(2, 44100.0f, length);  // TODO: hard-coded 44k?
  if (file_.exists()) {
    ptr<juce::FileInputStream> out(file_.createInputStream());
    if (out) {
      thumbnail_->loadFrom(*out);
      cacheWritten_ = thumbnail_->isFullyLoaded();
    } else {
      LOG(ERROR) << "Couldn't load from " << file_.getFullPathName();
    }
  }
}


void CachedThumbnail::addListener(Listener<juce::AudioThumbnail*>* listener) {
  Broadcaster<juce::AudioThumbnail*>::addListener(listener);
  (*listener)(thumbnail_.get());
}

CachedThumbnail::~CachedThumbnail() {
  // writeThumbnail();
}

void CachedThumbnail::operator()(const AudioSourceChannelInfo& i) {
  thumbnail_->addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);
  broadcast(thumbnail_.get());
}

void CachedThumbnail::writeThumbnail() {
  if (!cacheWritten_) {
    cacheWritten_ = true;
    ptr<juce::FileOutputStream> out(file_.createOutputStream());
    thumbnail_->saveTo(*out);
  }
}

}  // namespace util
}  // namespace audio
}  // namespace rec

