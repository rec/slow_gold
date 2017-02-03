#pragma once

#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

// Read mp3 tags into a StringPairArray.
Error getMp3Tags(mpg123_handle* mh, juce::StringPairArray* metadata);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

