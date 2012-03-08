#include "rec/audio/util/TrackBufferAndThumbnail.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/format/Manager.h"
#include "rec/base/Samples.h"
#include "rec/util/file/VirtualFile.h"

using namespace juce;

namespace rec {
namespace audio {
namespace util {

using rec::audio::source::RunnyProto;

static const int COMPRESSION = 256;

TrackBufferAndThumbnail::TrackBufferAndThumbnail()
    : cache_(1), cacheWritten_(false),
      thumbnail_(COMPRESSION, *format::getAudioFormatManager(), cache_) {
}

TrackBufferAndThumbnail::~TrackBufferAndThumbnail() {}

void TrackBufferAndThumbnail::addBlock(Samples<44100> pos, const Info& i) {
  Lock l(lock_);
  thumbnail_.addBlock(pos, *i.buffer, i.startSample, i.numSamples);
}

void TrackBufferAndThumbnail::writeThumbnail() {
  Lock l(lock_);
  if (cacheWritten_)
    return;

  cacheWritten_ = true;
  if (!thumbnail_.getTotalLength()) {
    // TODO: fix this.
    LOG(ERROR) << "writing empty cache";
  } else {
    file_.getParentDirectory().createDirectory();
    ptr<juce::FileOutputStream> out(file_.createOutputStream());
    if (!out)
    	LOG(ERROR) << "Unable to write file " << str(file_);
    else
      thumbnail_.saveTo(*out);
  }
}

Samples<44100> TrackBufferAndThumbnail::setReader(const VirtualFile& f, AudioFormatReader* reader) {
  Lock l(lock_);
  DCHECK(reader);
  DCHECK(reader->lengthInSamples);

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

