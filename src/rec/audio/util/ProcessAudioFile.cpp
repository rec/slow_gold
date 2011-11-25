#include "rec/audio/util/ProcessAudioFile.h"
#include "rec/audio/util/AudioFormatManager.h"

namespace rec {
namespace audio {
namespace util {

void processAudioFile(const File& in, const File& out,
                      SourceFilter filter) {
  CHECK(in.exists()) << "File " << str(in) << " doesn't exist";
  ptr<AudioFormatReader> reader(createReader(in));
  ptr<PositionableAudioSource> src(
      new AudioFormatReaderSource(reader.get(), false));

  if (out.exists())
    out.deleteFile();
  OutputStream* stream = out.createOutputStream();
  CHECK(stream) << "Couldn't create file " << str(out);

  AudioFormat* f = getAudioFormatManager()->
    findFormatForFileExtension(out.getFileExtension());
  CHECK(f) << "Couldn't find format for file " << str(out);

  ptr<AudioFormatWriter> writer(
      f->createWriterFor(stream,
                         reader->sampleRate,
                         reader->numChannels,
                         reader->bitsPerSample,
                         StringPairArray(),
                         0));
  CHECK(writer) << "Couldn't create writer for " << str(out);

  src.reset(filter(src.transfer()));
  writer->writeFromAudioSource(*src, static_cast<int>(src->getTotalLength()), 4096);
}

typedef std::pair<Source*, AudioFormatWriter*> SourceAndWriter;

SourceAndWriter makeSourceAndWriter(const File& in, const File& out) {
  CHECK(in.exists()) << "File " << str(in) << " doesn't exist";
  ptr<AudioFormatReader> reader(createReader(in));

  if (out.exists())
    out.deleteFile();
  OutputStream* stream = out.createOutputStream();
  CHECK(stream) << "Couldn't create file " << str(out);

  AudioFormat* f = getAudioFormatManager()->
    findFormatForFileExtension(out.getFileExtension());
  CHECK(f) << "Couldn't find format for file " << str(out);

  ptr<AudioFormatWriter> writer(
      f->createWriterFor(stream,
                         reader->sampleRate,
                         reader->numChannels,
                         reader->bitsPerSample,
                         StringPairArray(),
                         0));
  CHECK(writer) << "Couldn't create writer for " << str(out);

  return std::make_pair(new AudioFormatReaderSource(reader.transfer(), true),
                        writer.transfer());
}



}  // namespace util
}  // namespace audio
}  // namespace rec
