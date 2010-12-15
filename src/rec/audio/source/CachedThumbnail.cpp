#include "rec/audio/source/CachedThumbnail.h"

#include "rec/util/thread/FileWriter.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

CachedThumbnail::CachedThumbnail(const File& file)
  : file_(file),
    thumbnail_(compression, manager_, cache_) {}
  if (file_.exists()) {
    scoped_ptr<juce::FileInputStream> out(file_.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      return;
    }
    LOG(ERROR) << "Couldn't load from " << file_.getFullPathName().toCString();
  }
}

CachedThumbnail::~CachedThumbnail() {
  if (!thumbnail_.isFullyLoaded())
    writeThumbnail(false);
}

void CachedThumbnail::operator()(const AudioSourceChannelInfo& info) {
  if (!thumbnail_.isFullyLoaded()) {
    thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);
    if (thumbnail_.isFullyLoaded())
      writeThumbnail(true);
  }
}

void CachedThumbnail::writeThumbnail(bool deferred) {
  scoped_ptr<thread::FileWriter> writer(new thread::FileWriter(file_));
  juce::MemoryOutputStream mos(*writer->memory(), false);
  thumbnail_.saveTo(mos);
  if (deferred)
    writer.transfer()->startThread();
  else
    writer->run();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
