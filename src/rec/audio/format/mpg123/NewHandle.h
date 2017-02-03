#pragma once

#include "rec/audio/format/mpg123/Mpg123.h"


namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

// Create a new mpg123_handle for a Juce InputStream.
Error newHandle(juce::InputStream* in, mpg123_handle** mh);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

