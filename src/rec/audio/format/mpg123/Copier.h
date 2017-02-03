#pragma once

#include <stddef.h>

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

typedef long long int int64;

// A function that copies samples from source to destination.
typedef void (*Copier)(int** dest, int destChannels, int64 destOffset,
                                              void* source, int sourceChannels, int64 sourceSize);

// Get a Copier that matches the mp3 encoding.
Copier getCopier(int encoding);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

