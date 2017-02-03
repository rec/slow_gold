#pragma once

#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

// Represents a specific rate/channel/encoding we accept.
struct OutputFormat {
  long rate_;
  int channels_;
  mpg123_enc_enum encoding_;
};

// Create a reader from an InputStream, or return an error.  begin/end form a
// list of OutputFormats that we want to accept - if they're nullptr, or the same,
// we accept all formats.
Error createReader(juce::InputStream* sourceStream,
                   juce::AudioFormatReader** reader,
                   OutputFormat* begin = nullptr,
                   OutputFormat* end = nullptr);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
