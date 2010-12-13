#include "rec/audio/source/BufferySourceFactory.h"
#include "rec/audio/source/TrackSource.h"
#include "rec/widget/tree/VolumeFile.h"

using namespace rec::widget::tree;
using namespace util::thread;;

namespace rec {
namespace audio {
namespace source {

BufferySourceFactory::BufferySourceFactory(const VolumeFile& f, int blockSize)
    : Buffery(createSource(f), blockSize),
      file_(getShadowDirectory(f).getChildFile("thumbnail.stream")),
      thumbnailCache_(1),
      thumbnail_(thumbnailCache_) {
  if (file_.exists()) {
    scoped_ptr<FileInputStream> out(file.createInputStream());

    if (out)
      thumbnail_.loadFrom(*out);
    else
      LOG(ERROR) << "Couldn't read " << file_.getFullPathName().toCString();
  }
}

Source* BufferySourceFactory::newSource(int offset) {
  ScopedLock l(lock_);

  TrackSource* source = new TrackSource(this, offset);
  sources_.insert(source);
  return source;
}

void BufferySourceFactory::removeSource(TrackSource* source) {
  ScopedLock l(lock_);
  sources_.erase(source);
}

bool BufferySourceFactory::fill(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);
  bool full = Buffery::fill(info);

  if (!thumbnail_.isFullyLoaded()) {
    thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);

    if (thumbnail_.isFullyLoaded()) {
      File file = getThumbnailFile(file_);
      scoped_ptr<FileWriter> writer(new FileWriter(thumbnail_, file));

      thumbnail_.saveTo(*(writer->memory()));
      writer->release()->start();
    }
  }

  return full;
}

BufferySourceFactory::~BufferySourceFactory() {
  ScopedLock l(lock_);
  while (!sources_.empty())
    (*sources_.begin())->release();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
