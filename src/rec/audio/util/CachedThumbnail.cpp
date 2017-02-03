#include "rec/base/SampleRate.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/audio/format/Manager.h"

namespace rec {
namespace audio {
namespace util {

static const int COMPRESSION = 256;

CachedThumbnail::CachedThumbnail()
      : cacheWritten_(false),
        cache_(1),
        thumbnail_(COMPRESSION, *format::getReaderAudioFormatManager(), cache_) {
}

void CachedThumbnail::addBlock(SampleTime pos, const Info& i) {
  Lock l(lock_);
  thumbnail_.addBlock(pos, *i.buffer, i.startSample, i.numSamples);
}

void CachedThumbnail::write(const File& file) {
  Lock l(lock_);
  if (cacheWritten_)
    return;

  cacheWritten_ = true;
  DCHECK(thumbnail_.getTotalLength());
  if (thumbnail_.getTotalLength()) {
    file.getParentDirectory().createDirectory();
    std::unique_ptr<juce::FileOutputStream> out(file.createOutputStream());
    if (!out)
        LOG(ERROR) << "Unable to write file " << str(file);
    else
      thumbnail_.saveTo(*out);
  }
}

void CachedThumbnail::read(const File& file, SampleRate sampleRate,
                           SampleTime sampleLength, int channels) {
  thumbnail_.reset(channels, sampleRate, sampleLength);

#ifndef SLOWGOLD_SAVE_DISABLED
  if (file.exists()) {
    std::unique_ptr<juce::FileInputStream> out(file.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      cacheWritten_ = thumbnail_.isFullyLoaded();
    } else {
      LOG(ERROR) << "Couldn't load from " << file.getFullPathName();
    }
  } else {
    cacheWritten_ = false;
  }

#else
  cacheWritten_ = true;

#endif
}

}  // namespace util
}  // namespace audio
}  // namespace rec
