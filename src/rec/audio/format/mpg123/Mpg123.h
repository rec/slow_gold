#pragma once

// Constants and static functions for the mpg123 library.

#include "rec/base/base.h"
#include "include/mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

using Error = int;

// initializeOnce() initializes mpg123 and returns an error code.  As long as you
// have never called exitOnce(), you can call initializeOnce() as often as you
// like and it is thread-safe.
Error initializeOnce();

// Exit mpg123.  You can call this multiple times, but it is not thread-safe.
void exitOnce();

// The list of mp3 file extensions we recognize by default.
StringArray getMp3FileExtensions();

// The list of preferred samples rates - however, the decoder can apparently
// emit any sample rate you like.
juce::Array<int> getSampleRates();

// A list of all the possible bit depths - 8, 16, 32, 64.  Note that mpg123
// doesn't seem to be able to output 24 bit samples.  The MPG123_ENC_FLOAT_64 is
// the only example of a 64-bit type and I'm not sure if it's ever encountered
// in the wild...
juce::Array<int> getBitDepths();

// Number of bits per sample for this output encoding.
// encoding should be from mpg123_enc_enum.
int getBitsPerSample(int encoding);

// Get the name, translated into the current language.
String getTranslatedName();

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
