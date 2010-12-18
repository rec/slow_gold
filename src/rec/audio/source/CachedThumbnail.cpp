#include "rec/audio/source/CachedThumbnail.h"

#include "rec/util/thread/FileWriter.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

CachedThumbnail::CachedThumbnail(const File& file, int compression,
                                 int sampleLength)
  : file_(file),
    thumbnail_(compression, manager_, cache_),
    cache_(1),
    written_(false) {
  thumbnail_.reset(2, 44100.0f, sampleLength);  // TODO
  thumbnail_.createChannels(2);
  if (file_.exists()) {
    scoped_ptr<juce::FileInputStream> out(file_.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      written_ = true;
      return;
    }
    LOG(ERROR) << "Couldn't load from " << file_.getFullPathName().toCString();
  }
}


CachedThumbnail::~CachedThumbnail() {}

void CachedThumbnail::operator()(const AudioSourceChannelInfo& i) {
  thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);
  broadcast(thumbnail_);
}

void CachedThumbnail::writeThumbnail(bool deferred) {
  if (!written_) {
    scoped_ptr<thread::FileWriter> writer(new thread::FileWriter(file_));
    juce::MemoryOutputStream mos(*writer->memory(), false);
    thumbnail_.saveTo(mos);
    if (deferred)
      writer.transfer()->startThread();
    else
      writer->run();
    written_ = true;
  }
}


}  // namespace source
}  // namespace audio
}  // namespace rec
