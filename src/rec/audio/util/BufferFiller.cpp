#include "rec/audio/util/BufferFiller.h"

#include "rec/audio/util/CachedThumbnail.h"
#include "rec/audio/util/BufferedReaderImpl.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

using namespace rec::widget::waveform;

const int PARAMETER_WAIT = 1000;
static const char* FILENAME = "thumbnail.stream";

BufferFiller::BufferFiller()
    : thumbnail_(new CachedThumbnail),
      reader_(makeBufferedReader<short, 2>()),
      updateBuffer_(2, 1024),
      updateSource_(reader_->makeSource()) {
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}

BufferFiller::~BufferFiller() {}

bool BufferFiller::isFull() const {
  return reader_->isFull();
}

AudioThumbnail* BufferFiller::thumbnail() {
  return thumbnail_->thumbnail();
}

SampleTime BufferFiller::setReader(const VirtualFile& f,
                                   AudioFormatReader* reader) {
  Lock l(lock_);
  DCHECK(reader);
  DCHECK(reader->lengthInSamples);
  file_ = getShadowDirectory(f).getChildFile(FILENAME);
  thumbnail_->read(file_, reader->sampleRate, reader->lengthInSamples);
  return reader_->setReader(reader);
}

SampleRange BufferFiller::fillOnce() {
  SampleTime pos(reader_->position());
  int filled = static_cast<int>(reader_->fillNextBlock());

  if (filled) {
    updateInfo_.numSamples = filled;
    updateBuffer_.setSize(2, filled, false, false, true);
    updateSource_->setNextReadPosition(pos);
    updateSource_->getNextAudioBlock(updateInfo_);
    thumbnail_->addBlock(pos, updateInfo_);
  } else {
    thumbnail_->write(file_);
  }

  return SampleRange(pos, pos + filled);
}

void BufferFiller::reset() {
  reader_->reset();
}

}  // namespace util
}  // namespace audio
}  // namespace rec
