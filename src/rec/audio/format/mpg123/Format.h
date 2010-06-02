#ifndef __REC_AUDIO_FORMAT_MPG123_FORMAT__
#define __REC_AUDIO_FORMAT_MPG123_FORMAT__

#include "audio/audio_file_formats/juce_AudioFormat.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/format/mpg123/Reader.h"
#include "rec/audio/format/mpg123/Writer.h"
#include "rec/audio/format/mpg123/NewHandle.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

class Format : public AudioFormat {
 public:
	Format() : AudioFormat(getTranslatedName(), getMp3FileExtensions()) {}

	~Format() {}

  virtual AudioFormatReader* createReaderFor(InputStream* sourceStream,
                                             bool deleteStreamIfOpeningFails) {
    Error e;
    Reader* r = NULL;
    mpg123_handle *mh = NULL;
    if ((e == newHandle(sourceStream, &mh)) ||
        (e == processHandle(mh)) ||
        (e == Reader::create(sourceStream, mh, getFormatName(), &r))) {
      mpg123_delete(mh);

      if (deleteStreamIfOpeningFails)
        delete sourceStream;
      // TODO: report errors.
    }

    return r;
  }

  // Restrict this format to several files.
  virtual Error processHandle(mpg123_handle* handle) { return MPG123_OK; }

	virtual AudioFormatWriter* createWriterFor(OutputStream* streamToWriteTo,
                                             double sampleRateToUse,
                                             unsigned int numberOfChannels,
                                             int bitsPerSample,
                                             const StringPairArray& metadata,
                                             int qualityOptionIndex) {
    Writer* w = NULL;
    if (getPossibleBitDepths().contains(bitsPerSample)) {
      Writer::create(streamToWriteTo, getFormatName(), sampleRateToUse, numberOfChannels,
                     bitsPerSample, metadata, qualityOptionIndex, &w);
      // TODO: error handling
    }
    return w;
  }

	virtual const Array<int> getPossibleSampleRates() { return getSampleRates(); }
	virtual const Array<int> getPossibleBitDepths() { return getBitDepths(); }

	virtual bool canDoStereo() { return true; }
	virtual bool canDoMono() { return true; }
	virtual bool isCompressed() { return true; }

	juce_UseDebuggingNewOperator

 private:
  DISALLOW_COPY_AND_ASSIGN(Format);
};

class IntFormat : public Format {
 public:
  IntFormat() {}

  virtual Error processHandle(mpg123_handle* mh) {
    if (Error e = mpg123_format_none(mh))
      return e;
    if (Error e = mpg123_format(mh, 44100, MPG123_STEREO, MPG123_ENC_SIGNED_32))
      return e;
    return MPG123_OK;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(IntFormat);
};

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif // __REC_AUDIO_FORMAT_MPG123_FORMAT__
