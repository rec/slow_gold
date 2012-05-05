#include "rec/audio/util/CachedThumbnail.h"
#include "rec/audio/format/Manager.h"

namespace rec {
namespace audio {
namespace util {

static const int COMPRESSION = 256;

CachedThumbnail::CachedThumbnail()
      : cacheWritten_(false),
        cache_(1),
        thumbnail_(COMPRESSION, *format::getAudioFormatManager(), cache_) {
}

void CachedThumbnail::addBlock(Samples<44100> pos, const Info& i) {
  Lock l(lock_);
  thumbnail_.addBlock(pos, *i.buffer, i.startSample, i.numSamples);
}

void CachedThumbnail::write(const File& file) {
  Lock l(lock_);
  if (cacheWritten_)
    return;

  cacheWritten_ = true;
  if (!thumbnail_.getTotalLength()) {
    // TODO: fix this.
    LOG(ERROR) << "writing empty cache";
  } else {
    file.getParentDirectory().createDirectory();
    ptr<juce::FileOutputStream> out(file.createOutputStream());
    if (!out)
    	LOG(ERROR) << "Unable to write file " << str(file);
    else
      thumbnail_.saveTo(*out);
  }
}

void CachedThumbnail::read(const File& file, int64 sampleLength,
                           int channels, float sampleRate) {
  thumbnail_.reset(channels, sampleRate, sampleLength);  // TODO: hard-coded 44k?
  if (file.exists()) {
    ptr<juce::FileInputStream> out(file.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      cacheWritten_ = thumbnail_.isFullyLoaded();
    } else {
      LOG(ERROR) << "Couldn't load from " << file.getFullPathName();
    }
  } else {
    cacheWritten_ = false;
  }
}

}  // namespace util
}  // namespace audio
}  // namespace rec