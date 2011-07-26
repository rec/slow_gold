#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/util/AudioFormatManager.h"
#include "rec/base/SamplePosition.h"
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

void ThumbnailBuffer::addBlock(SamplePosition pos,
                               const AudioSourceChannelInfo& i) {
  thumbnail_.addBlock(pos, *i.buffer, i.startSample, i.numSamples);
}

void ThumbnailBuffer::writeThumbnail() {
  if (cacheWritten_)
    return;

  cacheWritten_ = true;
  if (!thumbnail_.getTotalLength()) {
    DLOG(ERROR) << "writing empty cache";

  } else if (!cacheWritten_) {
    ptr<juce::FileOutputStream> out(file_.createOutputStream());
    thumbnail_.saveTo(*out);
  }
}

bool ThumbnailBuffer::setReader(const VirtualFile& f) {
  ptr<AudioFormatReader> reader(source::createReaderAndLoadMetadata(f));
  if (reader) {
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
  } else if (!file::empty(f)) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
  }
  return buffer_.setReader(reader.transfer());
}

}  // namespace util
}  // namespace audio
}  // namespace rec

