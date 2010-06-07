#include <stdio.h>

#include <gtest/gtest.h>

#include "juce_amalgamated.h"
#include "rec/audio/format/mpg123/CreateReader.h"
#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

#include <stdio.h>

#include <gtest/gtest.h>

#include "juce_amalgamated.h"

#include "rec/audio/format/mpg123/CreateReader.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/format/mpg123/Format.h"
#include "rec/base/scoped_ptr.h"

using rec::audio::format::mpg123::Format;

int main(int argc, char * const argv[]) {
  if (argc > 3) {
    std::cerr << argv[0] << " Usage: Reader filein fileout\n";
    return -1;
  }

  const char* inName = (argc > 1) ? argv[0] : "../../../data/test1.mp3";
  const char* inName = (argc > 2) ? argv[0] : "../../../data/test1.wav";

  File infile(argv[1]);
  if (!infile.exists()) {
    std::cerr << "File " << argv[1] << " doesn't exist\n";
    return -1;
  }

  InputStream* in = infile.createInputStream();
  if (!in) {
    std::cerr << "Couldn't open input stream for " << argv[1] << "\n";
    return -1;
  }

  scoped_ptr<AudioFormatReader> reader(Format().createReaderFor(in, true));
  if (!reader) {
    std::cerr << "File " << argv[1] << " doesn't seem to be an mp3 file\n";
    return -1;
  }

  File outfile(argv[2]);
  if (outfile.exists()) {
    if (!outfile.deleteFile())
      std::cerr << "File " << argv[2] << " couldn't be deleted.\n";
    return -1;
  }

  OutputStream* outStream = outfile.createOutputStream();
  if (!outStream) {
    std::cerr << "Couldn't open output stream for " << argv[2] << "\n";
    return -1;
  }

  scoped_ptr<AudioFormatWriter> writer(
      WavAudioFormat().createWriterFor(outStream,
                                       reader->numChannels,
                                       reader->sampleRate,
                                       reader->bitsPerSample,
                                       reader->metadataValues,
                                       0));

  if (!writer) {
    std::cerr << "Couldn't open writer for " << argv[2] << "\n";
    return -1;
  }

  if (!writer->writeFromAudioReader(*reader, 0, reader->lengthInSamples)) {
    std::cerr << "Couldn't write for " << argv[2] << "\n";
    return -1;
  }

  std::cout << "Wrote " << argv[1] << " to " << argv[2] << "\n";
  return 0;
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
