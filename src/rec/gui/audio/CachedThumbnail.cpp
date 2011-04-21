#include "rec/gui/audio/CachedThumbnail.h"

#include "rec/util/thread/FileWriter.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/util/AudioFormatManager.h"

namespace rec {
namespace gui {
namespace audio {

CachedThumbnail::CachedThumbnail(const File& file, int compression,
                                 int sampleLength)
  : file_(file),
    thumbnail_(compression, *rec::audio::getAudioFormatManager(), cache_),
    cache_(1),
    isFull_(false) {
  thumbnail_.reset(2, 44100.0f, sampleLength);  // TODO
  if (file_.exists()) {
    ptr<juce::FileInputStream> out(file_.createInputStream());
    if (out) {
      thumbnail_.loadFrom(*out);
      isFull_ = true;
    } else {
      LOG(ERROR) << "Couldn't load from " << file_.getFullPathName();
    }
  }
}

CachedThumbnail::~CachedThumbnail() {}

void CachedThumbnail::operator()(const AudioSourceChannelInfo& i) {
  thumbnail_.addBlock(i.startSample, *i.buffer, i.startSample, i.numSamples);
  broadcast(true);
}

void CachedThumbnail::writeThumbnail(bool deferred) {
  if (!isFull_) {
    thread_ptr<thread::FileWriter> writer(new thread::FileWriter(file_));
    juce::MemoryOutputStream mos(*writer->memory(), false);
    thumbnail_.saveTo(mos);
    if (deferred)
      writer.transfer()->startThread();
    else
      writer->run();

    isFull_ = true;
  }
}

}  // namespace audio
}  // namespace gui
}  // namespace rec

