#include "rec/audio/source/BufferySourceFactory.h"
#include "rec/audio/source/TrackSource.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/util/thread/FileWriter.h"
#include "rec/util/thread/Trash.h"

using namespace rec::widget::tree;

namespace rec {
namespace audio {
namespace source {

BufferySourceFactory::BufferySourceFactory(const VolumeFile& f, int blockSize)
    : Buffery(createSource(f), blockSize),
      file_(getShadowDirectory(f).getChildFile("thumbnail.stream")),
      thumbnail_(512) {
  if (file_.exists()) {
    scoped_ptr<juce::FileInputStream> out(file_.createInputStream());

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

bool BufferySourceFactory::fill(const Block& block,
                                const AudioSourceChannelInfo& i) {
  ScopedLock l(lock_);
  bool full = Buffery::fill(block, i);

  if (!thumbnail_.isFullyLoaded()) {
    thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);

    if (thumbnail_.isFullyLoaded()) {
      scoped_ptr<thread::FileWriter> writer(new thread::FileWriter(file_));
      juce::MemoryOutputStream mos(*writer->memory(), false);
      thumbnail_.saveTo(mos);
      writer.transfer()->startThread();
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
