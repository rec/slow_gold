#include "rec/audio/util/CachedThumbnail.h"

#include "rec/util/thread/FileWriter.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/util/AudioFormatManager.h"

namespace rec {
namespace audio {
namespace util {

CachedThumbnail::CachedThumbnail(const File& file, int compression, int length)
  : file_(file),
    thumbnail_(compression, *rec::audio::getAudioFormatManager(), cache_),
    cache_(1),
    cacheWritten_(false) {
  thumbnail_.reset(2, 44100.0f, length);  // TODO: hard-coded 44k?
  if (file_.exists()) {
    ptr<juce::FileInputStream> out(file_.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      cacheWritten_ = thumbnail_.isFullyLoaded();
    } else {
      LOG(ERROR) << "Couldn't load from " << file_.getFullPathName();
    }
  }
}

void CachedThumbnail::addListener(Listener<juce::AudioThumbnail*>* listener) {
  Broadcaster<juce::AudioThumbnail*>::addListener(listener);
  (*listener)(&thumbnail_);
}

CachedThumbnail::~CachedThumbnail() {
  // writeThumbnail();
}

void CachedThumbnail::operator()(const AudioSourceChannelInfo& i) {
  thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);
  broadcast(&thumbnail_);
  if (thumbnail_.isFullyLoaded())
    writeThumbnail();
}

void CachedThumbnail::writeThumbnail() {
  if (!cacheWritten_) {
    cacheWritten_ = true;

    ptr<juce::FileOutputStream> out(file_.createOutputStream());
    thumbnail_.saveTo(*out);
#if 0
    thread_ptr<thread::FileWriter> writer(new thread::FileWriter(file_));
    juce::MemoryOutputStream mos(*writer->memory(), false);
    thumbnail_.saveTo(mos);
    writer->run();
#endif
  }
}

}  // namespace util
}  // namespace audio
}  // namespace rec

