#pragma once

#include <rec/base/base.h>

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

// A function that copies samples from source to destination.
using Copier = void (*)(int32** dest, int32 destChannels, int64 destOffset,
                        void* source, int32 sourceChannels, int64 sourceSize);

// Get a Copier that matches the mp3 encoding.
Copier getCopier(int32 encoding);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
