#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/util/AudioFormatManager.h"
#include "rec/base/Samples.h"
#include "rec/util/file/VirtualFile.h"

using namespace juce;

namespace rec {
namespace audio {
namespace util {

using rec::audio::source::RunnyProto;
using rec::audio::getAudioFormatManager;

static const int COMPRESSION = RunnyProto::default_instance().compression();

ThumbnailBuffer::ThumbnailBuffer()
    : cache_(1), cacheWritten_(false),
      thumbnail_(COMPRESSION, *rec::audio::getAudioFormatManager(), cache_) {
}

ThumbnailBuffer::~ThumbnailBuffer() {}

void ThumbnailBuffer::addBlock(Samples<44100> pos, const Info& i) {
  thumbnail_.addBlock(pos, *i.buffer, i.startSample, i.numSamples);
}

void ThumbnailBuffer::writeThumbnail() {
  if (cacheWritten_)
    return;

  cacheWritten_ = true;
  if (!thumbnail_.getTotalLength()) {
    // TODO: fix this.
    DLOG(ERROR) << "writing empty cache";
  } else {
    ptr<juce::FileOutputStream> out(file_.createOutputStream());
    thumbnail_.saveTo(*out);
  }
}

bool ThumbnailBuffer::setReader(const VirtualFile& f, AudioFormatReader* reader) {
  if (!reader) {
    LOG(ERROR) << "Thumbnail buffer had not reader";
    return false;
  }

  ptr<AudioFormatReader> r(reader);
  file_ = getShadowFile(f, "thumbnail.stream");

  thumbnail_.reset(2, 44100.0f, reader->lengthInSamples);  // TODO: hard-coded 44k?
  if (file_.exists()) {
    ptr<juce::FileInputStream> out(file_.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      cacheWritten_ = thumbnail_.isFullyLoaded();
    } else {
      LOG(ERROR) << "Couldn't load from " << file_.getFullPathName();
    }
  } else {
    cacheWritten_ = false;
  }

  return buffer_.setReader(r.transfer());
}

}  // namespace util
}  // namespace audio
}  // namespace rec

